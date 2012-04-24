/*
 * File:   cc1101.c
 * Author: Laurelindo
 *
 * Created on 06/03/2010 г., 2:08
 */
#include <avr/io.h>
#include <inttypes.h>
#include <util/atomic.h>
#include "cc2500.h"
#include "delay_util.h"

struct CC_t CC;



void CC_t::Init(void) {
    // Interrupts
    CC_GDO0_IRQ_DISABLE();
    EICRA |= (1<<ISC01)|(0<<ISC00); // Falling edge generates an interrupt
    EIFR  |= (1<<INTF0);            // Clear IRQ flag
    // Setup ports
    CC_DDR  &= ~((1<<CC_GDO0)|(1<<CC_MISO));
    CC_DDR  |=   (1<<CC_CS)|(1<<CC_MOSI)|(1<<CC_SCLK);
    CC_PORT |=   (1<<CC_GDO0)|(CC_MISO); // Enable pull-ups
    // Set initial values
    CC_SCLK_LO();
    CC_CS_HI();
    // Setup UART as SPI: MSB first, master, SCK idle low, f/4
    UCSR0C = (1<<UMSEL01)|(1<<UMSEL00)|(0<<UDORD0)|(0<<UCPHA0)|(0<<UCPOL0);
    UCSR0B = (1<<TXEN0)|(1<<RXEN0);
    UBRR0 = 1;
    // Variables
    NewPacketReceived = false;
    Reset();
    FlushRxFifo();
    RfConfig();
}

void CC_t::SetChannel(uint8_t AChannel) {
    while (CC.State != CC_STB_IDLE) EnterIdle();    // CC must be in IDLE mode
    WriteRegister(CC_CHANNR, AChannel);          // Now set channel
}

// ============================= Inner use =====================================
void CC_t::WriteBurst(uint8_t ARegAddr, uint8_t *PData, uint8_t ALength) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        CC_CS_LO();                                                   // Start transmission
        while (CC_MISO_IS_HI());                                      // Wait for chip to become ready
        ReadWriteByte(ARegAddr|CC_WRITE_FLAG|CC_BURST_FLAG);          // Address with write & burst flags
        for (uint8_t i=0; i<ALength; i++) ReadWriteByte(*PData++);    // Write bytes themselves
        CC_CS_HI();                                                   // End transmission
    } // atomic
}

void CC_t::ReadRX(uint8_t *PData, uint8_t ALength) {
    CC_CS_LO();                                                   // Start transmission
    while (CC_MISO_IS_HI());                                      // Wait for chip to become ready
    ReadWriteByte(CC_FIFO|CC_READ_FLAG|CC_BURST_FLAG);            // Address with read & burst flags
    for (uint8_t i=0; i<ALength; i++) *PData++ = ReadWriteByte(0);// Write bytes themselves
    CC_CS_HI();                                                   // End transmission
}

uint8_t CC_t::ReadRegister(uint8_t ARegAddr) {
    uint8_t FReply;
    ATOMIC_BLOCK(ATOMIC_FORCEON){
        CC_CS_LO();                               // Start transmission
        while (CC_MISO_IS_HI());                  // Wait for chip to become ready
        ReadWriteByte(ARegAddr | CC_READ_FLAG);   // Transmit header byte: set READ bit and BURST flag
        FReply = ReadWriteByte(0);                // Read reply
        CC_CS_HI();                               // End transmission
    }//atomic
    return FReply;
}
void CC_t::WriteRegister (uint8_t ARegAddr, uint8_t AData) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        CC_CS_LO();              // Start transmission
        while (CC_MISO_IS_HI()); // Wait for chip to become ready
        ReadWriteByte(ARegAddr); // Transmit header byte
        ReadWriteByte(AData);    // Write data
        CC_CS_HI();              // End transmission
    }//atomic
}
void CC_t::WriteStrobe (uint8_t AStrobe) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        CC_CS_LO();               // Start transmission
        while (CC_MISO_IS_HI());  // Wait for chip to become ready
        CC.State = ReadWriteByte(AStrobe);  // Write strobe
        CC_CS_HI();               // End transmission
        CC.State &= 0b01110000;   // Mask needed bits
    } // atomic
}

// **** Used to setup CC with needed values ****
void CC_t::RfConfig(void) {
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
    WriteRegister(CC_PKTLEN,   CC_PKT_DATA_LENGTH);  // Packet length.

    WriteRegister(CC_PATABLE, CC_PATABLE0_VALUE);

    WriteRegister(CC_MCSM2, CC_MCSM2_VALUE);
    WriteRegister(CC_MCSM1, CC_MCSM1_VALUE);
}


// ============================= Low level =====================================
uint8_t CC_t::ReadWriteByte(uint8_t AByte){
    UDR0 = AByte;	// Start transmission
    // Wait for transmission to complete
    //while (bit_is_clear (UCSR0A, TXC0));    // Wait until transmission completed
    while (bit_is_clear (UCSR0A, RXC0));    // Wait until reception completed
    uint8_t Response = UDR0;
    return Response;
}

// ============================ Interrupts =====================================
ISR(INT0_vect) {
    CC.NewPacketReceived = true;
}