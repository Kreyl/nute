/*
 * application.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: kreyl
 */

#include "application.h"
#include "cmd_uart.h"
#include "peripheral.h"
#include "sequences.h"
#include "eestore.h"
#include "lcd1200.h"
#include "evt_mask.h"

App_t App;
#define UART_RPL_BUF_SZ     36
//static uint8_t SBuf[UART_RPL_BUF_SZ];

#if 1 // ============================ Timers ===================================
static VirtualTimer ITmr;
void TmrOneSecondCallback(void *p) {
    chSysLockFromIsr();
    chEvtSignalI(App.PThd, EVTMASK_NEWSECOND);
    chVTSetI(&ITmr, MS2ST(TM_DOSE_INCREASE_MS), TmrOneSecondCallback, nullptr);
    chSysUnlockFromIsr();
}
#endif

#if 1 // ============================ Keys =====================================
static void KeyAny() {
    Beeper.Beep(BeepKey);
}

static void KeyStart() {

}
static void KeyTimeUp() {

}
static void KeyTimeDown() {

}
static void KeyCurrentUp() {

}
static void KeyCurrentDown() {

}
static void KeyStartLong() {

}
#endif

#if 1 // ========================= Application =================================
static WORKING_AREA(waAppThread, 256);
__attribute__((noreturn))
static void AppThread(void *arg) {
    chRegSetThreadName("App");
    uint32_t EvtMsk;
    while(true) {
        EvtMsk = chEvtWaitAny(ALL_EVENTS);
        // Keys
        if(EvtMsk & EVTMSK_KEY_START)        { KeyStart();       KeyAny(); }
        if(EvtMsk & EVTMSK_KEY_TIME_UP)      { KeyTimeUp();      KeyAny(); }
        if(EvtMsk & EVTMSK_KEY_TIME_DOWN)    { KeyTimeDown();    KeyAny(); }
        if(EvtMsk & EVTMSK_KEY_CURRENT_UP)   { KeyCurrentUp();   KeyAny(); }
        if(EvtMsk & EVTMSK_KEY_CURRENT_DOWN) { KeyCurrentDown(); KeyAny(); }
        if(EvtMsk & EVTMSK_KEY_START_LONG)   { KeyStartLong();   KeyAny(); }

        // TIme
        if(EvtMsk & EVTMASK_NEWSECOND) {
        }
    } // while 1
}

void App_t::Init() {
    // Interface init
    Lcd.PrintfFont(Times_New_Roman18x16, 18, 0, "0.0 mA ");
    Lcd.PrintfFont(Times_New_Roman18x16, 27, 2, "18:00");
    Lcd.Symbols(0, 4,
            LineHorizDouble, 7,
            LineHorizDoubleDown, 1,
            LineHorizDouble, 8,
            0);
    Lcd.Printf (0, 5, " Time  %c Current", LineVertDouble);
    Lcd.Symbols(7, 6, LineVertDouble, 1, 0);
    Lcd.Printf (0, 7, " 20:00 %c 1.0 mA", LineVertDouble);

    PThd = chThdCreateStatic(waAppThread, sizeof(waAppThread), NORMALPRIO, (tfunc_t)AppThread, NULL);
    // Timers init
    chSysLock();
    chVTSetI(&ITmr, MS2ST(1000), TmrOneSecondCallback, nullptr);
    chSysUnlock();
}
#endif

#if 1 // ======================= Command processing ============================
void Ack(uint8_t Result) { Uart.Cmd(0x90, &Result, 1); }

void UartCmdCallback(uint8_t CmdCode, uint8_t *PData, uint32_t Length) {
    switch(CmdCode) {
        case CMD_PING: Ack(OK); break;

        default: break;
    } // switch
}
#endif