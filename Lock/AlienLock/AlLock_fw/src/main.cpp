/*
 * File:   main.cpp
 * Author: Kreyl
 *
 * Created on May 27, 2011, 6:37 PM
 */

#include "stm32f10x.h"
#include "delay_util.h"
#include "sd.h"
#include "vs.h"
#include "media.h"
#include "kl_ini.h"
#include "sensors.h"
#include <string.h>
#include <stdlib.h>
#include "kl_util.h"
#include "keys.h"
#include "leds_pca.h"
#include "i2c_mgr.h"
#include "adc.h"
#include "uart_cmd.h"
#include "kl_lib.h"

#define FNAME_LNG_MAX   13
#define CODE_LNG_MAX    6

struct Settings_t {
    char SndKeyBeep[FNAME_LNG_MAX], SndKeyDrop[FNAME_LNG_MAX], SndPassError[FNAME_LNG_MAX], SndOpen[FNAME_LNG_MAX];
    char SndClose[FNAME_LNG_MAX], SndKeyCrash[FNAME_LNG_MAX];
    // Codes
    char CodeA[CODE_LNG_MAX+1], CodeB[CODE_LNG_MAX+1], ServiceCode[CODE_LNG_MAX+1]; // Because of trailing \0
    int8_t CodeALength, CodeBLength, ServiceCodeLength;     // Length of 0 means empty, negative length means crash
    // Colors
    Color_t ColorDoorOpen, ColorDoorOpening, ColorDoorClosed, ColorDoorClosing;
    uint32_t BlinkDelay;
    // Timings
    uint32_t DoorCloseDelay, KeyDropDelay;
    // Methods
    bool Read(void);
} Settings;

enum EntrResult_t {entNA, entError, entOpen};
struct Codecheck_t {
    uint32_t Timer;
    char EnteredCode[CODE_LNG_MAX+1];   // Because of trailing \0
    uint8_t EnteredLength;
    EntrResult_t EnterResult;
    void Task(void);
    void Reset(void) { EnteredLength=0; EnterResult=entNA; }
} Codecheck;

enum DoorState_t {dsClosed, dsOpened, dsOpening, dsClosing};
class Door_t {
private:
    klPin_t IPin;
    static void EvtJustClosed(void);
    static void EvtJustOpened(void);
    void LasersOn (void) { IPin.Clear(); }
    void LasersOff(void) { IPin.Set(); }
public:
    void Init(void) {
        IPin.Init(GPIOA, 11, GPIO_Mode_Out_PP);
        EvtJustClosed();
    }
    uint32_t Timer;
    DoorState_t State;
    void Task(void);
    void Open(void);
    void Close(void);
} Door;


// Prototypes
void GeneralInit(void);
void Event_Kbd(uint8_t AKbdSide, uint8_t AKey);

// ============================ Implementation ================================
int main(void) {
    GeneralInit();

    // ==== Main cycle ====
    while(1) {
        Keys.Task();
        ESnd.Task();
        Codecheck.Task();
        Door.Task();
        i2cMgr.Task();
        Leds.Task();
        Battery.Task();
        CmdUnit.Task();
        //Sensor.Task();
    } // while(1)
    return 0;
}

void GeneralInit(void) {
    UART_Init();
    // Disable JTAG
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    // Configure two bits for preemption priority
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

    // Init peripheral
    Delay.Init();
    Keys.Init();
    Keys.EvtKbd = Event_Kbd;
    CmdUnit.Init();
    // Sensor
//    Sensor.Init();
//    Sensor.EvtDetected = EVENT_SomeoneDetected;
    // Sound
    Vs.Init();
    ESnd.Init();

    // Leds
    i2cMgr.Init();
    Leds.Init();

    // Battery
    Battery.Init();
    Battery.State = bsFull;

    // Register filesystem
    f_mount(0, &SD.FatFilesystem);
    if (!Settings.Read()) while(1);    // nothing to do if config not read

    Door.Init();    // Door is closed during Init
    klPrintf("Lock is on\r");
    // Play initial sound
    ESnd.Play("alive.wav");
}

// ============================ Codecheck ======================================
void Codecheck_t::Task(void) {
    if (ESnd.State == sndPlaying) return;
    switch (Codecheck.EnterResult) {
        case entNA: // check if input timeout
            if((EnteredLength != 0) && Delay.Elapsed(&Timer, Settings.KeyDropDelay)) {
                Reset();
                ESnd.Play(Settings.SndKeyDrop);
            }
            break;
        case entError:
            Reset();
            ESnd.Play(Settings.SndPassError);
            break;
        case entOpen:
            Reset();
            Door.Open();
            break;
    } // switch
}

bool Settings_t::Read(void) {
    // Sound names
    if(!ReadString("Sound", "KeyBeep",   "lock.ini", Settings.SndKeyBeep,   FNAME_LNG_MAX)) return false;
    if(!ReadString("Sound", "KeyDrop",   "lock.ini", Settings.SndKeyDrop,   FNAME_LNG_MAX)) return false;
    if(!ReadString("Sound", "KeyCrash",  "lock.ini", Settings.SndKeyCrash,  FNAME_LNG_MAX)) return false;
    if(!ReadString("Sound", "PassError", "lock.ini", Settings.SndPassError, FNAME_LNG_MAX)) return false;
    if(!ReadString("Sound", "Open",      "lock.ini", Settings.SndOpen,      FNAME_LNG_MAX)) return false;
    if(!ReadString("Sound", "Close",     "lock.ini", Settings.SndClose,     FNAME_LNG_MAX)) return false;

    // ======= Codes =======
    // If length == 0 then code is empty. If code is negative (-1 for examle) then side is crashed
    // === Code A ===
    if(!ReadString("Code", "CodeA", "lock.ini", Settings.CodeA, CODE_LNG_MAX)) return false;
    Settings.CodeALength = strlen(Settings.CodeA);
    // Check if crashed
    if (Settings.CodeALength !=0) if (Settings.CodeA[0] == '-') Settings.CodeALength = -1;
    // === Code B ===
    if(!ReadString("Code", "CodeB", "lock.ini", Settings.CodeB, CODE_LNG_MAX)) return false;
    Settings.CodeBLength = strlen(Settings.CodeB);
    // Check if crashed
    if (Settings.CodeBLength !=0) if (Settings.CodeB[0] == '-') Settings.CodeBLength = -1;
    // === Service code ===
    if(!ReadString("Code", "ServiceCode", "lock.ini", Settings.ServiceCode, CODE_LNG_MAX)) return false;
    Settings.ServiceCodeLength = strlen(Settings.ServiceCode);

    // Colors
    if(!ReadColor("Colors", "DoorOpen", "lock.ini", &Settings.ColorDoorOpen)) return false;
    if(!ReadColor("Colors", "DoorOpening", "lock.ini", &Settings.ColorDoorOpening)) return false;
    if(!ReadColor("Colors", "DoorClosed", "lock.ini", &Settings.ColorDoorClosed)) return false;
    if(!ReadColor("Colors", "DoorClosing", "lock.ini", &Settings.ColorDoorClosing)) return false;
    if(!ReadUint32("Colors", "BlinkDelay", "lock.ini", &Settings.BlinkDelay)) return false;

    // Timings
    if(!ReadUint32("Timings", "DoorCloseDelay", "lock.ini", &Settings.DoorCloseDelay)) return false;
    if(!ReadUint32("Timings", "KeyDropDelay", "lock.ini", &Settings.KeyDropDelay)) return false;

    return true;
}

// ================================== Door =====================================
void Door_t::Open(void) {
    Door.State = dsOpening;
    ESnd.Play(Settings.SndOpen);
    ESnd.EvtPlayEnd = EvtJustOpened;
    Delay.Reset(&Timer);
    Leds.Led[0].Blink(Settings.ColorDoorOpening, Settings.BlinkDelay);
    Leds.Led[2].Blink(Settings.ColorDoorOpening, Settings.BlinkDelay);
}

void Door_t::Close(void) {
    Door.State = dsClosing;
    ESnd.Play(Settings.SndClose);
    ESnd.EvtPlayEnd = EvtJustClosed;
    Leds.Led[0].Blink(Settings.ColorDoorClosing, Settings.BlinkDelay);
    Leds.Led[2].Blink(Settings.ColorDoorClosing, Settings.BlinkDelay);
}

void Door_t::Task() {
    if (State == dsOpened) {
        if(Delay.Elapsed(&Timer, Settings.DoorCloseDelay))
            Close();
    }
}

void Door_t::EvtJustClosed(void) {
    ESnd.EvtPlayEnd = 0;
    Leds.Led[0].Solid(Settings.ColorDoorClosed);
    Leds.Led[2].Solid(Settings.ColorDoorClosed);
    Door.LasersOn();
    Door.State = dsClosed;
    klPrintf("Door is closed\r");
}
void Door_t::EvtJustOpened(void) {
    ESnd.EvtPlayEnd = 0;
    Door.State = dsOpened;
    Leds.Led[0].Solid(Settings.ColorDoorOpen);
    Leds.Led[2].Solid(Settings.ColorDoorOpen);
    Door.LasersOff();
    klPrintf("Door is opened\r");
}

// ================================== Battery ==================================
void Battery_t::Task() {
    if(!Delay.Elapsed(&Timer, 999)) return;
    Measure();
    // Discharging slope
    if ((State == bsFull) && (IValue < BATTERY_HALF)) {
        State = bsHalf;
        return;
    }
    if ((State == bsHalf) && (IValue < BATTERY_EMPTY)) {
        State = bsEmpty;
        return;
    }
    // Charging slope
    if ((State == bsHalf) && (IValue > (BATTERY_HALF+60))) {
        State = bsFull;
        return;
    }
    if ((State == bsEmpty) && (IValue > (BATTERY_EMPTY+60))) {
        State = bsHalf;
        return;
    }
    // Indicate discharged battery
    if ((State == bsEmpty) && (Door.State == dsClosed) && (Leds.Led[0].Mode != lmBlink)) {
        Leds.Led[0].Blink(Settings.ColorDoorClosed, Settings.BlinkDelay);
        Leds.Led[1].Blink(Settings.ColorDoorClosed, Settings.BlinkDelay);
    }
}


// ================================== Events ===================================
void KeyHandler(uint8_t RKey, int8_t RCodeLength, char *RCode) {
    // Check if crash
    if (RCodeLength < 0) {
        if (ESnd.State == sndStopped) ESnd.Play(Settings.SndKeyCrash);
        return;
    }
    // Digit entered
    if((RKey >= 0) && (RKey <=9)) {
        ESnd.Play(Settings.SndKeyBeep);     // Play sound always
        if (RCodeLength > 0) {
            if(Codecheck.EnteredLength < RCodeLength) {        // Digit entered is number 0...3
                Codecheck.EnteredCode[Codecheck.EnteredLength++] = '0' + RKey;
                Delay.Reset(&Codecheck.Timer);
            }
            else {  // Digit entered fifth time, this is error
                Codecheck.EnterResult = entError;
            }
        }// if (RCodeLength > 0)
    }
    else {  // none-digit
        if (RKey == KEY_STAR) {
            Delay.Bypass(&Codecheck.Timer, Settings.KeyDropDelay);  // Drop code
        }
        else if(RKey == KEY_HASH) {
            // Close door if open
            if (Door.State == dsOpened) { Door.Close(); }
            else if (Door.State == dsClosed) {
                if (RCodeLength == 0) Codecheck.EnterResult = entOpen;   // Open door in case of empty code
                else {  // Check code
                    if((Codecheck.EnteredLength == RCodeLength) && (strcmp(RCode, Codecheck.EnteredCode) == 0)) Codecheck.EnterResult = entOpen;  // Equal
                    else Codecheck.EnterResult = entError;
                }
            } // if open
        } // if hash
    } // if digit
}

void Event_Kbd(uint8_t AKbdSide, uint8_t AKey) {
    if (Codecheck.EnterResult != entNA) return; // disable keys in case of existing result
    //klPrintf("Key = %u %u\r", Keys.Kbd[0], Keys.Kbd[1]);
    if (AKbdSide == KBD_SIDE_A) KeyHandler(AKey, Settings.CodeALength, Settings.CodeA);
    else KeyHandler(AKey, Settings.CodeBLength, Settings.CodeB);
}
