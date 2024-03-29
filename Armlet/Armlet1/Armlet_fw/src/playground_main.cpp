/*
 * File:   main.cpp of Armlet1 project
 * Author: Kreyl
 * Date:   2012-09-13 10:11
 *
 */

#include "stm32f10x.h"
#include <stdlib.h>
#include "kl_lib.h"
#include "kl_assert.h"
#include "led.h"
#include "rf_comm.h"
#include "lcd1200.h"
#include "beep.h"
#include "battery.h"
#include "interface.h"
#include "kl_time.h"
#include "i2c_mgr.h"
#include "i2c_ee.h"
#include "keys.h"
#include "vibro.h"


// Prototypes
static void Init();

// ============================ Implementation =================================
void PlaygroundMain() {
    Init();

    // DEBUG
//    uint32_t Tmr;
//    uint8_t i=0, j=0;

    unsigned int cycle = 0;
    // ==== Main cycle ====
    while (1) {
		cycle++;

    	if (!assertion_raised) {

    		if (cycle % 103 == 0) {
				for (int i = 0; i < 40; i++)
					Lcd.PutPixel(i, i, 1);

				Lcd.SetDrawMode(OVERWRITE_INVERTED);
				Lcd.Printf(0, 1, "Hello, world!");
				Lcd.Printf(1, 3, "%08u", cycle);
				Lcd.SetDrawMode(OVERWRITE); // restore back
				Lcd.Printf(1, 2, "zzz");
    		}

    		// I know it's inefficient...
    		// But for testing, who cares?

			Lcd.Printf(0, 4, Keys.Up.IsPressed() ? "up" : "  ");
			Lcd.Printf(0, 5, Keys.Down.IsPressed() ? "down" : "    ");
			Lcd.Printf(0, 6, Keys.Enter.IsPressed() ? "enter" : "     ");

			if (Keys.Up.WasJustPressed() ||
				Keys.Down.WasJustPressed())
				Beep.Squeak(1, 5);

			if (Keys.Enter.WasJustPressed())
				Beep.Squeak(1, 10);

/*			Lcd.Printf(0, 1, "Hello, %s!", "world");
			Lcd.Printf(0, 2, "Cycle: %08u", cycle);
			Lcd.Printf(0, 3, "%c%c%c", 'a', 'b', 'c');*/
    	}

    	Uart.Task();
    	Lcd.Task();
        Vibro.Task();
    	if (!assertion_raised) {
			Battery.Task();
			Beep.Task();
			Interface.Task();
			Keys.Task();
			Radio.Task();
			i2cMgr.Task();
			Pill.Task();

			// Pill debug
//			if(Delay.Elapsed(&Tmr, 999)) {
//			    i++;
//			    if((Pill.State == esNew) or (Pill.State == esReady)) {
//			        if(i % 2 == 0) Pill.Write(7, &i, 1);
//			        else Pill.Read(7, &j, 1);
//			        Uart.Printf("i: %u; j: %u\r", i, j);
//			    }
//			    else Uart.Printf("Fail\r");
//			}
    	}
    } // while(1)
}

static inline void Init() {
    InitClock(clk2MHzInternal);
    klJtagDisable();

    Delay.Init();
    Uart.Init(115200);
    Uart.Printf("\rArmlet1\r");
    Lcd.Init();
    Lcd.Backlight(0);

    Interface.Init();
    Keys.Init();

    Battery.Init();
    Radio.Init();

    i2cMgr.Init();
    Pill.Init(INNER_EE_ADDR);

    Time.Init();

    Beep.Init();
    Beep.SetFreqHz(2007);
    Beep.Squeak(2, 4);

    Vibro.Init();
    Vibro.Flinch(2);

    // Get unique CPU ID and place it into packet to transmit
    GetUniqueID(&Radio.PktTx.IdArr[0]);
    Uart.Printf("ID: %08X %08X %08X\r", Radio.PktTx.IdArr[0], Radio.PktTx.IdArr[1], Radio.PktTx.IdArr[2]);
}
