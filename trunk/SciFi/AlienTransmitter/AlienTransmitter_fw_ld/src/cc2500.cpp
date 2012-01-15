/*
 * File:   cc1101.c
 * Author: Laurelindo
 *
 * Created on 06/03/2010 г., 2:08
 */
#include <inttypes.h>
#include "cc2500.h"
#include "cc2500_rf_settings.h"
#include "delay_util.h"


// ============================ Variables ======================================
CC_t CC;

// ========================== Implementation ===================================
void CC_t::Task(void) {
    // Handle New Packet
    if(NewPktRcvd) {
        klPrintf("ogo\r");
        if(EvtNewPkt != 0) EvtNewPkt();
        NewPktRcvd = false;
    }

    // Do with CC what needed
    GetState();
    switch (State) {
        case CC_STB_RX_OVF:
            klPrintf("RX ovf\r");
            FlushRxFIFO();
            break;
        case CC_STB_TX_UNDF:
            klPrintf("TX undf\r");
            FlushTxFIFO();
            break;

        case CC_STB_IDLE:
            //klPrintf("IDLE\r");
#ifdef CC_MODE_RX
//            EnterRX();
#else
            //if (Delay.Elapsed(&Timer, 300)) {
                klPrintf("TX\r");
                // Prepare packet to send
                TX_Pkt.ToAddr = 0x04;
                TX_Pkt.CommandID = 0xCA;
                TX_Pkt.SenderAddr = 18;
                WriteTX(TX_PktArray, CC_PKT_LEN);
                ////CC.EnterTXAndWaitToComplete();
                IRQDisable();
                EnterTX();
            //}
#endif
            break;

        case CC_STB_RX:
//            //klPrintf("RX\r");
//            if (GDO0_IsHi()) GDO0_WasHi = true;
//            // Check if GDO0 has fallen
//            else if (GDO0_WasHi) {
//                klPrintf(" IRQ\r");
//                GDO0_WasHi = false;
//                FifoSize = ReadRegister(CC_RXBYTES); // Get number of bytes in FIFO
//                if (FifoSize != 0) {
//                    ReadRX(RX_PktArray, (CC_PKT_LEN+2));    // Read two extra bytes of RSSI & LQI
//                    if(EvtNewPkt != 0) EvtNewPkt();
//                } // if size>0
//            } // if falling edge
            break;

        case CC_STB_TX:
            //klPrintf("TX1\r");
            break;

        default: // Just get out in other cases
            //klPrintf("Other: %X\r", State);
            //Uart.PrintString("\rOther: ");
            //Uart.PrintUint(CC.State);
            break;
    }//Switch
}

void CC_t::IRQHandler() {
    uint8_t FifoSize = ReadRegister(CC_RXBYTES); // Get number of bytes in FIFO
    FifoSize &= 0x7F;   // Remove MSB
    if (FifoSize != 0) {
        ReadRX(RX_PktArray, FifoSize);    // Read two extra bytes of RSSI & LQI
        //klPrintf("Rx Fifo: %X\r", FifoSize);
        if (FifoSize == (6+2)) {
            NewPktRcvd = true;
            klPrintf("aga\r");
        }
    } // if size>0
}

void CC_t::Init(void) {
    // ******** Hardware init section *******
    // ==== Clocks init ====
#ifndef STM32F10X_LD_VL
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
#else
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO, ENABLE);
#endif
    IRQDisable();   // Do not enable IRQ before CC init
    // ==== GPIO init ====
    GPIO_InitTypeDef GPIO_InitStructure;
#ifndef STM32F10X_LD_VL
    // Enable pin alternate functions
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1); // SCK
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1); // MISO
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1); // MOSI
    // Init pins
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    // SPI pins
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // Configure CC_CS as Push-Pull output
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // Configure CC_GDO as Input Pull-up
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#else
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // Configure CS as Push-Pull output
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // Configure CLK & MOSI as Alternate Function Push Pull
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // Configure MISO as Input Floating
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // Configure CC_GDO as Input Pull-up
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    CS_Hi();

    // === DEBUG ===
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
//    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // ==== IRQ ====
#ifndef STM32F10X_LD_VL
    // Enable SYSCFG clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    // Connect EXTI0 Line to PA3 pin
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);
    // Configure EXTI3 line
    EXTI_InitTypeDef   EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
#endif
    // ==== SPI init ====    MSB first, master, SCK idle low
    SPI_I2S_DeInit(SPI1);
    SPI_InitTypeDef SPI_InitStructure;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
    SPI_InitStructure.SPI_FirstBit  = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);
    // =========== Firmware init section ===========
    Reset();
    FlushRxFIFO();
    RfConfig();
    SetChannel(150);
    SetAddress(4);
}

void CC_t::SetChannel(uint8_t AChannel) {
    // CC must be in IDLE mode
    while (State != CC_STB_IDLE) EnterIdle();
    // Now set channel
    WriteRegister(CC_CHANNR, AChannel);
}

void CC_t::EnterTXAndWaitToComplete(void) {
    EnterTX();
    // Wait for packet to transmit completely
    while (!GDO0_IsHi());   // After this, SYNC word is transmitted
    while (GDO0_IsHi());    // After this, packet is transmitted
}

// ============================= Inner use =====================================
void CC_t::IRQEnable(void) {
    // Enable and set EXTI3 Interrupt to the lowest priority
    NVIC_InitTypeDef   NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
void CC_t::IRQDisable(void) {
    NVIC_InitTypeDef   NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void CC_t::EnterRX(void) {
    NewPktRcvd = false;
    WriteStrobe(CC_SRX);
    IRQEnable();
}

void CC_t::WriteTX (uint8_t *PData, uint8_t ALength) {
    CS_Lo();                 // Start transmission
    BusyWait();              // Wait for chip to become ready
    ReadWriteByte(CC_FIFO|CC_WRITE_FLAG|CC_BURST_FLAG);         // Address with write & burst flags
    for (uint8_t i=0; i<ALength; i++) ReadWriteByte(*PData++);  // Write bytes themselves
    CS_Hi();                 // End transmission
}
void CC_t::ReadRX  (uint8_t *PData, uint8_t ALength){
    CS_Lo();                 // Start transmission
    BusyWait();              // Wait for chip to become ready
    ReadWriteByte(CC_FIFO|CC_READ_FLAG|CC_BURST_FLAG);              // Address with read & burst flags
    for (uint8_t i=0; i<ALength; i++) *PData++ = ReadWriteByte(0);  // Write bytes themselves
    CS_Hi();                 // End transmission
}

uint8_t CC_t::ReadRegister (uint8_t ARegAddr){
    CS_Lo();      // Start transmission
    BusyWait();   // Wait for chip to become ready
    ReadWriteByte(ARegAddr | CC_READ_FLAG);     // Transmit header byte
    uint8_t FReply = this->ReadWriteByte(0);    // Read reply
    CS_Hi();      // End transmission
    return FReply;
}
void CC_t::WriteRegister (uint8_t ARegAddr, uint8_t AData){
    CS_Lo();                 // Start transmission
    BusyWait();              // Wait for chip to become ready
    ReadWriteByte(ARegAddr); // Transmit header byte
    ReadWriteByte(AData);    // Write data
    CS_Hi();                 // End transmission
}
void CC_t::WriteStrobe (uint8_t AStrobe){
    CS_Lo();      // Start transmission
    BusyWait();   // Wait for chip to become ready
    State = ReadWriteByte(AStrobe);  // Write strobe
    CS_Hi();      // End transmission
    State &= 0b01110000; // Mask needed bits
}

// **** Used to setup CC with needed values ****
void CC_t::RfConfig(void){
    WriteRegister(CC_FSCTRL1,  CC_FSCTRL1_VALUE);    // Frequency synthesizer control.
    WriteRegister(CC_FSCTRL0,  CC_FSCTRL0_VALUE);    // Frequency synthesizer control.
    WriteRegister(CC_FREQ2,    CC_FREQ2_VALUE);      // Frequency control word, high byte.
    WriteRegister(CC_FREQ1,    CC_FREQ1_VALUE);      // Frequency control word, middle byte.
    WriteRegister(CC_FREQ0,    CC_FREQ0_VALUE);      // Frequency control word, low byte.
    WriteRegister(CC_MDMCFG4,  CC_MDMCFG4_VALUE);    // Modem configuration.
    WriteRegister(CC_MDMCFG3,  CC_MDMCFG3_VALUE);    // Modem configuration.
    WriteRegister(CC_MDMCFG2,  CC_MDMCFG2_VALUE);    // Modem configuration.
    WriteRegister(CC_MDMCFG1,  CC_MDMCFG1_VALUE);    // Modem configuration.
    WriteRegister(CC_MDMCFG0,  CC_MDMCFG0_VALUE);    // Modem configuration.
    WriteRegister(CC_CHANNR,   CC_CHANNR_VALUE);     // Channel number.
    WriteRegister(CC_DEVIATN,  CC_DEVIATN_VALUE);    // Modem deviation setting (when FSK modulation is enabled).
    WriteRegister(CC_FREND1,   CC_FREND1_VALUE);     // Front end RX configuration.
    WriteRegister(CC_FREND0,   CC_FREND0_VALUE);     // Front end RX configuration.
    WriteRegister(CC_MCSM0,    CC_MCSM0_VALUE);      // Main Radio Control State Machine configuration.
    WriteRegister(CC_FOCCFG,   CC_FOCCFG_VALUE);     // Frequency Offset Compensation Configuration.
    WriteRegister(CC_BSCFG,    CC_BSCFG_VALUE);      // Bit synchronization Configuration.
    WriteRegister(CC_AGCCTRL2, CC_AGCCTRL2_VALUE);   // AGC control.
    WriteRegister(CC_AGCCTRL1, CC_AGCCTRL1_VALUE);   // AGC control.
    WriteRegister(CC_AGCCTRL0, CC_AGCCTRL0_VALUE);   // AGC control.
    WriteRegister(CC_FSCAL3,   CC_FSCAL3_VALUE);     // Frequency synthesizer calibration.
    WriteRegister(CC_FSCAL2,   CC_FSCAL2_VALUE);     // Frequency synthesizer calibration.
    WriteRegister(CC_FSCAL1,   CC_FSCAL1_VALUE);     // Frequency synthesizer calibration.
    WriteRegister(CC_FSCAL0,   CC_FSCAL0_VALUE);     // Frequency synthesizer calibration.
    WriteRegister(CC_FSTEST,   CC_FSTEST_VALUE);     // Frequency synthesizer calibration.
    WriteRegister(CC_TEST2,    CC_TEST2_VALUE);      // Various test settings.
    WriteRegister(CC_TEST1,    CC_TEST1_VALUE);      // Various test settings.
    WriteRegister(CC_TEST0,    CC_TEST0_VALUE);      // Various test settings.
    WriteRegister(CC_FIFOTHR,  CC_FIFOTHR_VALUE);    // fifo threshold
    WriteRegister(CC_IOCFG2,   CC_IOCFG2_VALUE);     // GDO2 output pin configuration.
    WriteRegister(CC_IOCFG0,   CC_IOCFG0_VALUE);     // GDO0 output pin configuration.
    WriteRegister(CC_PKTCTRL1, CC_PKTCTRL1_VALUE);   // Packet automation control.
    WriteRegister(CC_PKTCTRL0, CC_PKTCTRL0_VALUE);   // Packet automation control.
    WriteRegister(CC_PKTLEN,   CC_PKT_LEN);          // Packet length.

    WriteRegister(CC_PATABLE, CC_PATABLE0_VALUE);

    WriteRegister(CC_MCSM2, CC_MCSM2_VALUE);
    WriteRegister(CC_MCSM1, CC_MCSM1_VALUE);
}

uint8_t CC_t::ReadWriteByte(uint8_t AByte) {
    SPI1->DR = AByte;
    while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));  // Wait for SPI transmission to complete
    return SPI1->DR;
}

// ================================= Interrupt ================================
void EXTI3_IRQHandler(void) {
#ifndef STM32F10X_LD_VL
    if(EXTI_GetITStatus(EXTI_Line3) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line3); // Clear the EXTI line pending bit
        //klPrintf(" IRQ\r");
        CC.IRQHandler();
    }
#endif
}
