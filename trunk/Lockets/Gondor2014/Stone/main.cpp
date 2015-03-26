/*
 * File:   main.cpp
 * Author: Kreyl
 * Project: Armlet2South
 *
 * Created on Feb 05, 2013, 20:27
 */

#include "kl_lib_L15x.h"
#include "ch.h"
#include "hal.h"
#include "clocking_L1xx.h"
#include "cmd_uart.h"
#include "cc1101defins.h"
#include "rlvl1_defins.h"
#include "cc1101.h"

#include "led_rgb.h"

// rpkt
#define MAGIC_NUMBER    (uint32_t)0xCA110FE5    // Call of Elwen Star
const rPkt_t rPktTx = { MAGIC_NUMBER };
rPkt_t rPktRx;


int main(void) {
    // ==== Init Vcore & clock system ====
    SetupVCore(vcore1V2);
    Clk.UpdateFreqValues();
    // ==== Init OS ====
    halInit();
    chSysInit();

    // ==== Init Hard & Soft ====
    Uart.Init(115200);
    Led.Init();
    //Led.SetColor(clWhite);
    Uart.Printf("\rGondorStone    AHB=%u", Clk.AHBFreqHz);

    // Init radioIC
    CC.Init();
    CC.SetTxPower(CC_PwrPlus10dBm);
    CC.SetPktSize(RPKT_LEN);
    CC.SetChannel(9);

    int8_t Rssi;
    while(true) {
        // Try to receive
        uint8_t RxRslt = CC.ReceiveSync(99, &rPktRx, &Rssi);
        if((RxRslt == OK) and (rPktRx.MagicNumber == MAGIC_NUMBER)) {
            Led.SetColor(clGreen);
            Uart.Printf("\r%d", Rssi);
        }
        else Led.SetColor(clBlack);

    } // while true
}