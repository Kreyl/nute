/*
 * File:   main.c of Tirusse of Tirusse project
 * Author: Kreyl Laurelindo
 *
 * Created on 2010.04.07
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include <util/atomic.h>

#include "ring.h"
#include "cc1101.h"
#include "time_utils.h"
#include "common.h"
#include "battery.h"

// ================================= Global ====================================
uint16_t LEDTimer;
enum CCPwr_t {HiPwr, LoPwr};
struct {
    uint16_t Timer;
    enum CCPwr_t Pwr;
} CCSrv;

// =============================== General =====================================
int main(void) {
    GeneralInit();
    DDRA = 1<<PA0;   // DEBUG
    // ******** Main cycle *********
    while (1){
        wdt_reset();    // Reset watchdog
        CC_Task();
        LED_Task();
        Battery_Task();
    } // while 1
}

FORCE_INLINE void GeneralInit(void){
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    TimerInit();
    // LED init
    LED_DDR |= (1<<LED_P);
    // CC init
    TimerResetDelay(&CCSrv.Timer);
    CC.TX_Pkt.PacketID = 1;
    CC_Init();
    CCSrv.Pwr = HiPwr;
    CC_SetChannel(45);   // Set needed channel
    // Battery
    BatteryInit();
    sei();
}

// ================================ Tasks ======================================
void LED_Task(void) {
    if ((Battery.ADCState == ADCNoMeasure) && BATTERY_IS_DISCHARGED()) {
        LED_ON();
        return;
    }
    if (TimerDelayElapsed(&LEDTimer, LED_ON_PERIOD)) LED_OFF();
}

void CC_Task (void){
    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State){
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;

        case CC_STB_IDLE:
            PORTA &= ~(1<< PA0);
            if (CCSrv.Pwr == HiPwr) {
                if (TimerDelayElapsed(&CCSrv.Timer, 999)) {
                    PORTA |= (1<< PA0);
                    CC_SetPwr(CC_PWR_10DBM);// Set Hi TX power
                    // LED on
                    TimerResetDelay(&LEDTimer);
                    LED_ON();
                    // Prepare CALL packet
                    CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LEN); // Write bytes to FIFO
                    CC_ENTER_TX();
                    CCSrv.Pwr = LoPwr;      // Next time transmit at lo pwr
                } // if delay elapsed
            } // if Hi Pwr
            else { // Lo Power
                // Transmit at lo pwr immediately after Hi Pwr transmission ended
                CC_SetPwr(CC_PWR_M6DBM);    // Set Lo TX power
                // Prepare CALL packet
                CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LEN); // Write bytes to FIFO
                CC_ENTER_TX();
                CCSrv.Pwr = HiPwr;          // Next time transmit at hi pwr
                ATOMIC_BLOCK(ATOMIC_FORCEON) {
                    CC.TX_Pkt.PacketID++;   // Next time transmit other ID
                }
            }
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}


// =============================== Events ======================================

