#include "stm32f10x.h"
#include <stdlib.h>
#include "kl_lib.h"
#include "kl_assert.h"
#include "led.h"
#include "rf_comm.h"
#include "lcd1200.h"
#include "beep.h"
#include "battery.h"
#include "i2c_mgr.h"
#include "i2c_ee.h"
#include "keys.h"
#include "vibro.h"
#include "force.h"

Force_t Force;

const int SPEEDUP = 10;


const int LIGHT_FULL = 3;
const int LIGHT_FADE = 3;
const int LIGHT_INTENSITY = 20;

int light = 0;

void Lighten() {
	light = 10*(LIGHT_FULL+LIGHT_FADE);
}

void BacklightTask() {
	static uint32_t t=0;
	if (Keys.AnyKeyWasJustPressed())
		Lighten();
	if (!Delay.Elapsed(&t, 100))
		return;
	if (light > 0)
		light--;
	if (light > 10*LIGHT_FADE)
		Lcd.Backlight(LIGHT_INTENSITY);
	else
		Lcd.Backlight(LIGHT_INTENSITY*light/(LIGHT_FADE*10));
}

int rnd100() {
	int x = rand();
	x &= 0x0FFFFFFF; // to deal with negative shit
	return x%100;
}


enum UIState_t {
	IDLE,
	MENU,
	NOTIFICATION,
};

UIState_t state = IDLE;

//void DrawForce() {
//	static int y = 0;
//	y = (y+1)%60;
//	for (int i = 0; i < 12; i++)
//		for (int j = 0; j < 65; j++)
//			Lcd.PutPixel(i, j, 0);
//	for (int i = 0; i < 5; i++) {
//		Lcd.PutPixel(5, y+i, 1);
//		Lcd.PutPixel(3+i, y, 1);
//	}
//}

const char *menu_items[] = {
	"������ ���� ",
	"����/���� ������               �", // :(
	"������ ������� ",
	"����/���� ������",
	"������ ������ ",
};
int menu_index = 0;
const int TIME_IN_MENU = 45; // in tenths of a second
int time_in_menu;

void DrawMenu() {
	Lcd.Printf(0, 2, "������...");
	for (unsigned int i = 0; i < countof(menu_items); i++) {
		if (i == menu_index)
			Lcd.SetDrawMode(OVERWRITE_INVERTED);
		else
			Lcd.SetDrawMode(OVERWRITE);
		Lcd.Printf(0, i==0 ? 1 : i+2, "%s", menu_items[i]);
	}
	Lcd.SetDrawMode(OVERWRITE);
}

const int W = LCD_STR_WIDTH-2; // for jedi stuff
const int H = LCD_STR_HEIGHT;

const int MAX_STATUS_LENGTH = 1000;
const int MAX_STATUS_LINES = MAX_STATUS_LENGTH/(W-2);

char status[MAX_STATUS_LENGTH+1] = "None";
char status_lines[MAX_STATUS_LINES][W+1];
int num_status_lines = 0;
int scroll_position = 0;

void DrawIdleScreen() {
	for (int row = 0; row < H; row++) {
		int i = row+scroll_position;
		if (i >= 0 && i < num_status_lines)
			Lcd.Printf(2, row, "%s", status_lines[i]);
		else {
			for (int j = 0; j < W; j++)
				Lcd.Printf(j+2, row, " ");
		}
	}

	Lcd.SetDrawMode(OVERWRITE_INVERTED);
	if (scroll_position > 0)
		Lcd.Printf((W-5)/2+2, 0, " %c%c%c ", 0x18, 0x18, 0x18);
	if (scroll_position+H < num_status_lines)
		Lcd.Printf((W-5)/2+2, H-1, " %c%c%c ", 0x19, 0x19, 0x19);
	Lcd.SetDrawMode(OVERWRITE);
}

void SetStatus(const char *new_status) {
	assert(strlen(new_status) <= MAX_STATUS_LENGTH);
	assert(W > 1);
	if (strcmp(status, new_status) == 0)
		return;
	strcpy(status, new_status);
	num_status_lines = 1;
	char *cur_line = status_lines[0];
	int i = 0;
	bool write_spaces = true;
	for (const char *p = new_status; ; p++) {
		bool need_new_line = false;
		if (*p == 0)
			need_new_line = true;
		else if (i == W)
			need_new_line = true;
		else if (i == W-1 &&
				 p[-1] == ' ' &&
				 p[0] != 0 && p[0] != ' ' &&
				 p[1] != ' ' && p[1] != '\n')
			need_new_line = true;
		else if (*p == '\n')
			need_new_line = true;
		// finalize current line
		if (need_new_line) {
			// TODO: replace filler with ' ' in release
			while (i < W)
				cur_line[i++] = '^';
			cur_line[i] = 0;
		}
		if (*p == 0)
			break;
		// add new line
		if (need_new_line) {
			cur_line = status_lines[num_status_lines++];
			i = 0;
			write_spaces = (*p == '\n');
		}

		if (*p != '\n' && (*p != ' ' || write_spaces))
			cur_line[i++] = *p;

		if (*p != ' ')
			write_spaces = true;
	}
	assert(num_status_lines <= MAX_STATUS_LINES);
	scroll_position = 0;

	if (state == IDLE) {
		Vibro.Flinch(1);
		DrawIdleScreen();
	}
}


const int MAX_NOTIFICATION_LENGTH = 100;
char notification[MAX_NOTIFICATION_LENGTH] = "none";
int notification_time;
int notification_timeout;


void DrawNotification() {
	Lcd.Printf(0, 1, "%s", notification);
	if (notification_time < 30)
		return;
	int color = notification_time / 5 % 2;
	for (int i = 0; i <= 6; i++) {
		Lcd.PutPixel(LCD_WIDTH-1-i, LCD_HEIGHT-1-i, color);
		Lcd.PutPixel(LCD_WIDTH-1, LCD_HEIGHT-1-i, color);
		Lcd.PutPixel(LCD_WIDTH-1-i, LCD_HEIGHT-1, color);
	}
}

void SetNotification(const char *text, int timeout) {
	assert(strlen(text) <= MAX_NOTIFICATION_LENGTH);
	strcpy(notification, text);
	state = NOTIFICATION;
	Lcd.Cls();
	Vibro.Flinch(2);
	notification_timeout = timeout*10;
	if (timeout >= 0)
		Lighten();
	notification_time = 0;
}


PillData_t pill_data;

enum PillState_t {
	PILL_NONE,
	PILL_READING,
	PILL_INSERTED,
} pill_state;

void PillInserted();
void PillRemoved();

void ProcessPill() {
	switch (pill_state) {
	case PILL_NONE:
		if (Pill.State == esNew || Pill.State == esReady) {
			Pill.Read(0, (uint8_t*)&pill_data, 2);
			pill_state = PILL_READING;
		}
		break;
	case PILL_READING:
		if (Pill.State == esReady) {
			pill_state = PILL_INSERTED;
			PillInserted();
		}
		else if (Pill.State == esFailure) {
			pill_state = PILL_NONE;
		}
		break;
	case PILL_INSERTED:
		if (Pill.State == esFailure || Pill.State == esNew) {
			pill_state = PILL_NONE;
			PillRemoved();
		}
		break;
	}
}

int health = 1000;
int bleeding = 0; // 0, 1 or 2
int respirator = 0; // 0 - none, 1 - resp, 2 - broken

const char *GetStatus() {
	char *messages[10];
	int num_messages = 0;

	if (health < 0) {
		if (health != -666) {
			SetNotification("� ����(��)", -1);
			health = -666;
		}
		return "� ����(�)";
	}


#define ADD_MESSAGE(m) (messages[num_messages++] = (m))

	if (bleeding == 1)
		ADD_MESSAGE("� ���� ������������");
	else if (bleeding == 2)
		ADD_MESSAGE("������ �������");

	if (health > 800) {
	}
	else if (health > 600) {
		ADD_MESSAGE("������ ����� ��������");
	}
	else if (health > 400) {
		ADD_MESSAGE("��� ����� ������������� ����");
	}
	else if (health > 200) {
		ADD_MESSAGE("�� ���� ������ ���� �� �����������");
	}
	else {
		ADD_MESSAGE("� ��� ��������");
	}

	if (respirator == 0)
		ADD_MESSAGE("� ��� �����������");
	else if (respirator == 1)
		ADD_MESSAGE("� � �����������");
	else if (respirator == 2)
		ADD_MESSAGE("� � ��������� �����������");

#undef ADD_MESSAGE

	char buf[1000] = "";
	for (int i = 0; i < num_messages; i++) {
		if (i > 0)
			strcpy(buf+strlen(buf), "; ");
		strcpy(buf+strlen(buf), messages[i]);
	}
	return buf;
}

void SavePill() {
	Pill.Write(0, (uint8_t*)&pill_data, 2);
}

void PillInserted() {
	if (pill_data.Type == 3) {
		SetNotification("������� ����������", 3);
		respirator = 1;
	}
	else if (pill_data.Type == 0) {
		if (pill_data.ChargeCount > 0) {
			SetNotification("����� ��������", 3);
			pill_data.ChargeCount = 0;
			SavePill();
			if (bleeding != 2)
				bleeding = 0;
			health += 400;
			if (health > 1000)
				health = 1000;
		}
		else {
			SetNotification("������ ��������� �� �����", 3);
		}
	}
	else if (pill_data.Type == 2) {
		if (pill_data.ChargeCount > 0) {
			SetNotification("��������� ��������", 3);
			pill_data.ChargeCount = 0;
			SavePill();
			if (bleeding != 0)
				bleeding -= 1;
		}
		else {
			SetNotification("��������������� ������������ ��������", 3);
		}
	}
}

void PillRemoved() {
	if (pill_data.Type == 3) {
		SetNotification("������ ����������", 3);
		respirator = 0;
	}
}

void MedicineTask() {
	if (rnd100() >= 10*SPEEDUP)
		return;
	if (health == -666)
		return;
	if (rnd100() < 40)
		health -= bleeding;
}

void Wound(int index) {
	if (index == 1 || index == 3) {
		if (bleeding < 2)
			bleeding++;
		health -= 200;
		SetNotification("���� ������ � ����������!", 3);
	}
	else {
		bleeding = 2;
		health -= 300;
		SetNotification("���� ������ � ������!", 3);
	}
}

void Task() {
	switch (state) {
	case IDLE:
	    Force.DrawForce();
		MedicineTask();
		SetStatus(GetStatus());
		if (Keys.Up.WasJustPressed()) {
			if (scroll_position > 0) {
				scroll_position--;
				DrawIdleScreen();
			}
		}
		if (Keys.Down.WasJustPressed()) {
			if (scroll_position+H < num_status_lines) {
				scroll_position++;
				DrawIdleScreen();
			}
		}
		if (Keys.Enter.WasJustPressed()) {
			menu_index = 0;
			time_in_menu = TIME_IN_MENU;
			state = MENU;
			Lcd.Cls();
			DrawMenu();
		}
		ProcessPill();
		break;
	case MENU:
		if (Keys.Up.WasJustPressed()) {
			menu_index--;
			if (menu_index < 0)
				menu_index = 0;
			time_in_menu = TIME_IN_MENU;
			DrawMenu();
		}
		if (Keys.Down.WasJustPressed()) {
			menu_index++;
			if (menu_index >= (int)countof(menu_items))
				menu_index = (int)countof(menu_items)-1;
			time_in_menu = TIME_IN_MENU;
			DrawMenu();
		}
		time_in_menu--;
		if (time_in_menu == 0 || Keys.Enter.WasJustPressed()) {
			if (time_in_menu == 0)
				menu_index = 0;
			if (menu_index > 0) {
				Wound(menu_index);
			}
			else {
				state = IDLE;
				Lcd.Cls();
				DrawIdleScreen();
			}
		}
		break;
	case NOTIFICATION:
		if (Keys.Up.WasJustPressed()) {
		}
		if (Keys.Down.WasJustPressed()) {
		}
		if (Keys.Enter.WasJustPressed() && notification_time >= 10) {
			state = IDLE;
			Lcd.Cls();
			DrawIdleScreen();
		}

		if (notification_timeout < 0) {
			if (notification_time == 10 ||
				notification_time == 50 ||
				notification_time == 150 ||
				(notification_time >= 250 && notification_time % 20 == 0))
				Vibro.Flinch(2);
		}

		DrawNotification();
		notification_time++;
		if (notification_timeout > 0 && notification_time > notification_timeout) {
			state = IDLE;
			Lcd.Cls();
			DrawIdleScreen();
		}
		break;
	}
}


static void Init();

void ArmletMain() {
	static uint32_t t = 0;
    Init();

    Force.IsForceUser = true; // DEBUG

    Lcd.Cls();

    SetStatus("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.");
    DrawIdleScreen();

    while (1) {
    	Uart.Task();
    	Lcd.Task();
        Vibro.Task();

    	if (assertion_raised)
    		continue;
		//Battery.Task();
		Beep.Task();
		Keys.Task();
		Radio.Task();
		i2cMgr.Task();
		Pill.Task();
		BacklightTask();

		if (Delay.Elapsed(&t, 100))
			Task();

		// logic goes here (perhaps in a separate task-like function, whatever)
    }
}

static inline void Init() {
    InitClock(clk2MHzInternal);
    klJtagDisable();

    Delay.Init();
    Uart.Init(115200);
    Uart.Printf("\rArmlet\r");
    Lcd.Init();
    Lcd.Backlight(0);

    Keys.Init();

    Battery.Init();
    Radio.Init();

    i2cMgr.Init();
    Pill.Init(PILL_ADDR);

    Beep.Init();
    Beep.SetFreqHz(2007);
    Beep.Squeak(2, 4);

    Vibro.Init();
    Vibro.Flinch(2);

    // Get unique CPU ID and place it into packet to transmit
    GetUniqueID(&Radio.PktTx.IdArr[0]);
    Uart.Printf("ID: %08X %08X %08X\r", Radio.PktTx.IdArr[0], Radio.PktTx.IdArr[1], Radio.PktTx.IdArr[2]);
}
