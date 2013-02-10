/*
 * beep.cpp
 *
 *  Created on: 07.02.2013
 *      Author: kreyl
 */

#include "beep.h"

#define BEEP_TOP_VALUE   270 // 100% volume means on/off ratio 1/1

Beep_t Beep;

// ==== Beep Thread ====
static WORKING_AREA(waBeepThread, 128);
static msg_t BeepThread(void *arg) {
    (void)arg;
    chRegSetThreadName("Beep");
    while(1) Beep.Squeak();
    return 0;
}

void Beep_t::Init() {
    PChunk = NULL;
    ResetOccured = false;
    // GPIO
    PinSetupAlterFunc(GPIOA, 11, omPushPull, pudNone, AF2);
    // Timer
    rccEnableTIM1(FALSE);
    TIM1->CR1 = TIM_CR1_CEN; // Enable timer, set clk division to 0, AutoReload not buffered
    TIM1->CR2 = 0;
    TIM1->ARR = BEEP_TOP_VALUE;
    TIM1->BDTR = TIM_BDTR_MOE | TIM_BDTR_AOE;
    // Output
    TIM1->CCR4 = 0;     // Initially, volume = 0
    TIM1->CCMR1 = 0;    // Outputs disabled
    TIM1->CCMR2 = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;  // Output4, PWM mode1
    //TIM1->CCER = TIM_CCER_CC4E; // Output4 enabled
    // Thread
    PThread = chThdCreateStatic(waBeepThread, sizeof(waBeepThread), NORMALPRIO, BeepThread, NULL);
}

void Beep_t::Squeak() {
    if(PChunk == NULL) {
        // Put thread to sleep, it will be waken when new sequence is ready
        chSysLock();
        chSchGoSleepS(THD_STATE_SUSPENDED);
        chSysUnlock();
    }
    else {
        chSysLock();
        uint8_t Volume = PChunk->VolumePercent;
        uint16_t Delay = PChunk->Time_ms;
        if(Volume > 100) Volume = 100;
        if(Volume > 0) {
            SetFreqHz(PChunk->Freq_Hz);
            On(Volume);
        }
        else Off();
        chSysUnlock();
        chThdSleepMilliseconds(Delay);
        if(ResetOccured) ResetOccured = false;
        else {
            // Check if last chunk
            if(PChunk == &Buf[BEEP_MAX_CHUNK_COUNT-1]) {
                PChunk = NULL;
                Off();
            }
            else PChunk++;
        } // if reset
    }
}

void Beep_t::SetFreqHz(uint32_t FreqHz) {
    uint32_t FPrescaler = Clk.APBFreqHz / (BEEP_TOP_VALUE * FreqHz);
    if(FPrescaler != 0) FPrescaler--;   // do not decrease in case of high freq
    TIM1->PSC = (uint16_t)FPrescaler;
}

// ==== Feeding data ====
FeederRetVal_t Beep_t::FeedStart(uint8_t Byte) {
    if(Byte == NTS_BEEP) {  // Good MsgType
        Reset();
        return frvOk;
    }
    else return frvNoMore;
}

#define MAX_BYTE_CNT    (BEEP_MAX_CHUNK_COUNT * BEEP_CHUNK_SZ)
FeederRetVal_t Beep_t::FeedData(uint8_t Byte) {
    *PFeedData = Byte;
    FdrByteCnt++;
    // Check if last possible byte received
    if(FdrByteCnt >= MAX_BYTE_CNT) {
        FeederEndPkt(); // Start beep
        return frvNoMore;
    }
    PFeedData++;
    return frvOk;
}

void Beep_t::FeederEndPkt() {
    ChunkCnt = FdrByteCnt / BEEP_CHUNK_SZ;
    if(ChunkCnt > 0) {
        PChunk = Buf;
        chSysLock();
        chSchWakeupS(PThread, 0);
        chSysUnlock();
    }
}
