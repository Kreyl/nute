/*
 * pill.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: g.kruglov
 */

#include "pill.h"

Pill_t Pill[PILL_CNT];
EventSource IEvtPillChange;

static i2c_t i2c;

void PillReset();

// =============================== Thread ======================================
static WORKING_AREA(waPillThread, 256);
static msg_t PillThread(void *arg) {
    (void)arg;
    chRegSetThreadName("Pill");

    //uint8_t Rslt;
    uint8_t Buf[7];
    Buf[0] = 9;
    Buf[1] = 0xA5;
    Pill[0].Write(Buf, 4);
    Buf[0] = 0;
    Buf[1] = 0;

    while(1) {
        chThdSleepMilliseconds(27);
        // Check if i2c error
        if(i2c.Error) {
            Uart.Printf("Err\r");
            PillReset();
        }
        // Discover if pill status changed
//        bool OldState, HasChanged = false;
//        for(uint8_t i=0; i<PILL_CNT; i++) {
//            OldState = Pill[i].Connected;       // Save current state

        if(Pill[0].Read(Buf, 4) == OK) Uart.Printf("%A\r", Buf, 4, ' ');
//        Rslt = Pill[0].CheckIfConnected();
//        if(Rslt == OK) Uart.Printf("Ok\r");

//            if(Pill[i].Connected != OldState) HasChanged = true;
//        } // for
//        if(HasChanged) chEvtBroadcast(&IEvtPillChange);
    } // while 1
    return 0;
}

void PillDeinit() {
    PinClear(PERIPH_PWR_GPIO, PERIPH_PWR_PIN);
    chThdSleepMilliseconds(1);  // Allow power to fade
    PinSetupAnalog(PERIPH_PWR_GPIO, PERIPH_PWR_PIN);    // Power
    i2c.Standby();
}

void PillInit() {
    PillDeinit();
    PinSetupOut(PERIPH_PWR_GPIO, PERIPH_PWR_PIN, omPushPull);   // Power
    PinSet(PERIPH_PWR_GPIO, PERIPH_PWR_PIN);
    chThdSleepMilliseconds(1);  // Allow power to rise
    i2c.Init(PILL_I2C, PILL_I2C_GPIO, PILL_SCL_PIN, PILL_SDA_PIN, PILL_I2C_BITRATE_HZ, PILL_DMATX, PILL_DMARX);
    // Firmware
    chEvtInit(&IEvtPillChange);
    // Pills
    for(uint8_t i=0; i<PILL_CNT; i++) Pill[i].Init(i);
    // Thread
    chThdCreateStatic(waPillThread, sizeof(waPillThread), NORMALPRIO, PillThread, NULL);
}

void PillReset() {
    PillDeinit();
    PinSetupOut(PERIPH_PWR_GPIO, PERIPH_PWR_PIN, omPushPull);   // Power
    PinSet(PERIPH_PWR_GPIO, PERIPH_PWR_PIN);
    chThdSleepMilliseconds(1);  // Allow power to rise
    i2c.Resume();
}

void PillRegisterEvtChange(EventListener *PEvtLstnr, uint8_t EvtMask) {
    chEvtRegisterMask(&IEvtPillChange, PEvtLstnr, EvtMask);
}

// =============================== Pill_t ======================================
void Pill_t::Init(uint8_t IcAddr) {
    IAddr = IcAddr;
    Connected = false;
    chBSemInit(&ISem, NOT_TAKEN);
}

uint8_t Pill_t::Read(uint8_t *Ptr, uint8_t Length) {
    if(chBSemWaitTimeout(&ISem, TIME_INFINITE) != RDY_OK) return FAILURE;
    uint8_t WordAddress = PILL_START_ADDR;
    uint8_t Rslt = i2c.CmdWriteRead(EEADDR+IAddr, &WordAddress, 1, Ptr, Length);
    Connected = (Rslt == OK);
    if(i2c.Error == true) PillReset();
    chBSemSignal(&ISem);
    return Rslt;
}

uint8_t Pill_t::CheckIfConnected() {
    if(chBSemWaitTimeout(&ISem, TIME_INFINITE) != RDY_OK) return FAILURE;
    uint8_t Rslt = i2c.CmdWriteWrite(EEADDR+IAddr, NULL, 0, NULL, 0);
    Connected = (Rslt == OK);
    if(i2c.Error == true) PillReset();
    chBSemSignal(&ISem);
    return Rslt;
}

// TODO: write by pages
uint8_t Pill_t::Write(uint8_t *Ptr, uint8_t Length) {
    if(chBSemWaitTimeout(&ISem, TIME_INFINITE) != RDY_OK) return FAILURE;
    uint8_t WordAddress = PILL_START_ADDR;
    uint8_t Rslt = i2c.CmdWriteWrite(EEADDR+IAddr, &WordAddress, 1, Ptr, Length);
    Connected = (Rslt == OK);
    if(Rslt == OK) chThdSleepMilliseconds(5);   // Allow memory to complete writing
    if(i2c.Error == true) PillReset();
    chBSemSignal(&ISem);
    return Rslt;

}
