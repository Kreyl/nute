/*
 * kl_lib_f205.h
 *
 *  Created on: 10.12.2012
 *      Author: kreyl
 */

#ifndef KL_LIB_F2XX_H_
#define KL_LIB_F2XX_H_

#include "stm32f2xx.h"
#include "ch.h"
#include "hal.h"
#include "clocking.h"
#include "string.h"     // for memcpy
#include "cmd_uart.h"

// =============================== General =====================================
#define PACKED __attribute__ ((__packed__))
#ifndef countof
#define countof(A)  (sizeof(A)/sizeof(A[0]))
#endif

// Return values
#define OK              0
#define FAILURE         1
#define TIMEOUT         2
#define BUSY            3
#define NEW             4
#define IN_PROGRESS     5
#define LAST            6

// Binary semaphores
#define NOT_TAKEN       false
#define TAKEN           true

enum BitOrder_t {boMSB, boLSB};
enum LowHigh_t {Low, High};

// DMA
#define DMA_PRIORITY_LOW        STM32_DMA_CR_PL(0b00)
#define DMA_PRIORITY_MEDIUM     STM32_DMA_CR_PL(0b01)
#define DMA_PRIORITY_HIGH       STM32_DMA_CR_PL(0b10)
#define DMA_PRIORITY_VERYHIGH   STM32_DMA_CR_PL(0b11)

// ============================ Simple delay ===================================
static inline void DelayLoop(volatile uint32_t ACounter) { while(ACounter--); }
static inline void Delay_ms(uint32_t Ams) {
    volatile uint32_t __ticks = (Clk.AHBFreqHz / 4000) * Ams;
    DelayLoop(__ticks);
}

// ===================== Single pin manipulations ==============================
enum PinOutMode_t {
    omPushPull  = 0,
    omOpenDrain = 1
};
enum PinPullUpDown_t {
    pudNone = 0b00,
    pudPullUp = 0b01,
    pudPullDown = 0b10
};
enum PinSpeed_t {
    ps2MHz  = 0b00,
    ps25MHz = 0b01,
    ps50MHz = 0b10,
    ps100MHz = 0b11
};
enum PinAF_t {
    AF0=0, AF1=1, AF2=2, AF3=3, AF4=4, AF5=5, AF6=6, AF7=7,
    AF8=8, AF9=9,AF10=10, AF11=11, AF12=12, AF13=13, AF14=14, AF15=15
};

// Set/clear
static inline void PinSet    (GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) { PGpioPort->BSRRL = (uint32_t)(1<<APinNumber); }
static inline void PinClear  (GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) { PGpioPort->BSRRH = (uint32_t)(1<<APinNumber); }
static inline void PinToggle (GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) { PGpioPort->ODR  ^= (uint32_t)(1<<APinNumber); }
// Check state
static inline bool PinIsSet(GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) { return (PGpioPort->IDR & (uint32_t)(1<<APinNumber)); }
// Setup
static inline void PinClockEnable(GPIO_TypeDef *PGpioPort) {
    if     (PGpioPort == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if(PGpioPort == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if(PGpioPort == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if(PGpioPort == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    else if(PGpioPort == GPIOE) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
}
// GPIOA, 1, omPushPull/omOpenDrain, pudNone/pudPullUp/pudPullDown, ps2MHz/ps25MHz/ps50MHz/ps100MHz
static inline void PinSetupOut(
        GPIO_TypeDef *PGpioPort,
        const uint16_t APinNumber,
        const PinOutMode_t PinOutMode,
        const PinPullUpDown_t APullUpDown = pudNone,
        const PinSpeed_t ASpeed = ps50MHz) {
    // Clock
    PinClockEnable(PGpioPort);
    // Setup mode
    PGpioPort->MODER &= ~(0b11 << (APinNumber*2));  // clear previous bits
    PGpioPort->MODER |= 0b01 << (APinNumber*2);     // Set new bits
    // Setup output type
    PGpioPort->OTYPER &= ~(1<<APinNumber);
    PGpioPort->OTYPER |= (uint32_t)PinOutMode << APinNumber;
    // Setup Pull-Up or Pull-Down
    PGpioPort->PUPDR &= ~(0b11 << (APinNumber*2)); // clear previous bits
    PGpioPort->PUPDR |= (uint32_t)APullUpDown << (APinNumber*2);
    // Setup speed
    PGpioPort->OSPEEDR &= ~(0b11 << (APinNumber*2)); // clear previous bits
    PGpioPort->OSPEEDR |= (uint32_t)ASpeed << (APinNumber*2);
}
static inline void PinSetupIn(
        GPIO_TypeDef *PGpioPort,
        const uint16_t APinNumber,
        const PinPullUpDown_t APullUpDown
        ) {
    // Clock
    PinClockEnable(PGpioPort);
    // Setup mode
    PGpioPort->MODER &= ~(0b11 << (APinNumber*2));          // clear previous bits
    // Setup Pull-Up or Pull-Down
    PGpioPort->PUPDR &= ~(0b11 << (APinNumber*2)); // clear previous bits
    PGpioPort->PUPDR |= (uint32_t)APullUpDown << (APinNumber*2);
}
static inline void PinSetupAnalog(GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) {
    // Clock
    PinClockEnable(PGpioPort);
    // Setup mode
    PGpioPort->MODER |= 0b11 << (APinNumber*2);  // Set new bits
    // Setup Pull-Up or Pull-Down
    PGpioPort->PUPDR &= ~(0b11 << (APinNumber*2)); // clear previous bits
    PGpioPort->PUPDR |= (uint32_t)pudNone << (APinNumber*2);
}
static inline void PinSetupAlterFunc(
        GPIO_TypeDef *PGpioPort,
        const uint16_t APinNumber,
        const PinOutMode_t PinOutMode,
        const PinPullUpDown_t APullUpDown,
        const PinAF_t AAlterFunc,
        const PinSpeed_t ASpeed = ps50MHz) {
    // Clock
    PinClockEnable(PGpioPort);
    // Setup mode
    PGpioPort->MODER &= ~(0b11 << (APinNumber*2));  // clear previous bits
    PGpioPort->MODER |= 0b10 << (APinNumber*2);     // Set new bits
    // Setup output type
    PGpioPort->OTYPER &= ~(1<<APinNumber);
    PGpioPort->OTYPER |= (uint32_t)PinOutMode << APinNumber;
    // Setup Pull-Up or Pull-Down
    PGpioPort->PUPDR &= ~(0b11 << (APinNumber*2)); // clear previous bits
    PGpioPort->PUPDR |= (uint32_t)APullUpDown << (APinNumber*2);
    // Setup speed
    PGpioPort->OSPEEDR &= ~(0b11 << (APinNumber*2)); // clear previous bits
    PGpioPort->OSPEEDR |= (uint32_t)ASpeed << (APinNumber*2);
    // Setup Alternate Function
    uint32_t n = (APinNumber <= 7)? 0 : 1;      // 0 if 0...7, 1 if 8..15
    uint32_t Shift = 4 * ((APinNumber <= 7)? APinNumber : APinNumber - 8);
    PGpioPort->AFR[n] &= ~(0b1111 << Shift);
    PGpioPort->AFR[n] |= (uint32_t)AAlterFunc << Shift;
}

// Fast switch
static inline void PinFastOutPP(GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) {
    // Setup mode
    PGpioPort->MODER &= ~(0b11 << (APinNumber*2));  // clear previous bits
    PGpioPort->MODER |= 0b01 << (APinNumber*2);     // Set new bits
}

class PwmPin_t {
private:
    uint32_t *PClk;
    TIM_TypeDef* Tim;
public:
    __IO uint32_t *PCCR;    // Made public to allow DMA
    void SetFreqHz(uint32_t FreqHz);
    void Init(GPIO_TypeDef *GPIO, uint16_t N, uint8_t TimN, uint8_t Chnl, uint16_t TopValue, bool Inverted=false);
    void On(uint16_t Brightness) { *PCCR = Brightness; }
    void Off() { *PCCR = 0; }
};

// ================================= DEBUG =====================================
void chDbgPanic(const char *msg1);

// ================================= SPI =======================================
enum CPHA_t {cphaFirstEdge, cphaSecondEdge};
enum CPOL_t {cpolIdleLow, cpolIdleHigh};
enum SpiBaudrate_t {
    sbFdiv2   = 0b000,
    sbFdiv4   = 0b001,
    sbFdiv8   = 0b010,
    sbFdiv16  = 0b011,
    sbFdiv32  = 0b100,
    sbFdiv64  = 0b101,
    sbFdiv128 = 0b110,
    sbFdiv256 = 0b111,
};

static inline void SpiSetup(
        SPI_TypeDef *Spi,
        BitOrder_t BitOrder,
        CPOL_t CPOL,
        CPHA_t CPHA,
        SpiBaudrate_t Baudrate
        ) {
    // Clocking
    if      (Spi == SPI1) { rccEnableSPI1(FALSE); }
    else if (Spi == SPI2) { rccEnableSPI2(FALSE); }
    else if (Spi == SPI3) { rccEnableSPI3(FALSE); }
    // Mode: Master, NSS software controlled and is 1, 8bit, NoCRC, FullDuplex
    Spi->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_MSTR;
    if(BitOrder == boLSB) Spi->CR1 |= SPI_CR1_LSBFIRST;     // MSB/LSB
    if(CPOL == cpolIdleHigh) Spi->CR1 |= SPI_CR1_CPOL;      // CPOL
    if(CPHA == cphaSecondEdge) Spi->CR1 |= SPI_CR1_CPHA;    // CPHA
    Spi->CR1 |= ((uint16_t)Baudrate) << 3;                  // Baudrate
    Spi->CR2 = 0;
    Spi->I2SCFGR &= ~((uint16_t)SPI_I2SCFGR_I2SMOD);        // Disable I2S
}

static inline void SpiEnable (SPI_TypeDef *Spi) { Spi->CR1 |=  SPI_CR1_SPE; }
static inline void SpiDisable(SPI_TypeDef *Spi) { Spi->CR1 &= ~SPI_CR1_SPE; }

// =============================== I2C =========================================
class i2c_t {
private:
    I2C_TypeDef *ii2c;
    GPIO_TypeDef *IPGpio;
    uint16_t ISclPin, ISdaPin;
    void SendStart() { ii2c->CR1 |= I2C_CR1_START; }
    void IStop()   { ii2c->CR1 |= I2C_CR1_STOP; }
    void IAck()    { ii2c->CR1 |= I2C_CR1_ACK; }
    void IEnable() { ii2c->CR1 |= I2C_CR1_PE; }
    bool RxIsNotEmpty() { return (ii2c->SR1 & I2C_SR1_RXNE); }
    void ClearAddrFlag() { (void)ii2c->SR1; (void)ii2c->SR2; }
    uint8_t IWaitFlagSet(uint16_t *Reg, uint16_t Flags) {
        uint32_t RetryCnt = 4096;
        while(RetryCnt--) if(*Reg & Flags) return OK;
        return TIMEOUT;
    }
    uint8_t IBusyWait() {
        uint8_t RetryCnt = 4;
        while(RetryCnt--) {
            if(!(ii2c->SR2 & I2C_SR2_BUSY)) return OK;
            chThdSleepMilliseconds(1);
        }
        Error = true;
        return TIMEOUT;
    }
    //void IClearFlags() { ii2c->s
public:
    bool Error;
    void Init(I2C_TypeDef *pi2c, GPIO_TypeDef *PGpio, uint16_t SclPin, uint16_t SdaPin) {
        ii2c = pi2c;
        IPGpio = PGpio;
        ISclPin = SclPin;
        ISdaPin = SdaPin;
        Deinit();
        Error = false;
        // GPIOs
        PinSetupAlterFunc(PGpio, SclPin, omOpenDrain, pudNone, AF4);
        PinSetupAlterFunc(PGpio, SdaPin, omOpenDrain, pudNone, AF4);
        // Clock and reset
        if      (ii2c == I2C1) { rccEnableI2C1(FALSE); rccResetI2C1(); }
        else if (ii2c == I2C2) { rccEnableI2C2(FALSE); rccResetI2C2(); }
        else if (ii2c == I2C3) { rccEnableI2C3(FALSE); rccResetI2C3(); }
        // Minimum clock is 2 MHz
        uint32_t ClkMhz = Clk.APB1FreqHz / 1000000;
        uint16_t tmpreg = ii2c->CR2;
        tmpreg &= (uint16_t)~I2C_CR2_FREQ;
        if(ClkMhz < 2)  ClkMhz = 2;
        if(ClkMhz > 30) ClkMhz = 30;
        tmpreg |= ClkMhz;
        ii2c->CR2 = tmpreg;
        ii2c->CR1 &= (uint16_t)~I2C_CR1_PE; // Disable i2c to setup TRise & CCR
        ii2c->TRISE = (uint16_t)(((ClkMhz * 300) / 1000) + 1);
        // 16/9
        tmpreg = (uint16_t)((Clk.APB1FreqHz / 400000) * 25);
        if(tmpreg == 0) tmpreg = 1; // minimum allowed value
        ii2c->CCR = I2C_CCR_FS | I2C_CCR_DUTY | tmpreg;
        ii2c->CR1 |= I2C_CR1_PE;    // Enable i2c back
    }

    void Deinit() {
        if      (ii2c == I2C1) { rccResetI2C1(); rccDisableI2C1(FALSE); }
        else if (ii2c == I2C2) { rccResetI2C2(); rccDisableI2C2(FALSE); }
        else if (ii2c == I2C3) { rccResetI2C3(); rccDisableI2C3(FALSE); }
        // Disable GPIOs
        PinSetupAnalog(IPGpio, ISclPin);
        PinSetupAnalog(IPGpio, ISdaPin);
    }

    uint8_t Cmd(uint8_t Addr, uint8_t *WPtr, uint8_t WLength, uint8_t *RPtr, uint8_t RLength) {
        if(IBusyWait() != OK) return FAILURE;
        // Clear flags
        ii2c->SR1 = 0;
        while(RxIsNotEmpty()) (void)ii2c->DR;   // Read DR until it empty
        ClearAddrFlag();
        // Start transmission
        SendStart();
        if(WaitEv5() != 0) return FAILURE;


        return OK;
    }
};

#endif /* KL_LIB_F2XX_H_ */