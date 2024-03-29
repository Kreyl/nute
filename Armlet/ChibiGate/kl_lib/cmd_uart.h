/*
 * cmd_uart.h
 *
 *  Created on: 15.04.2013
 *      Author: kreyl
 */

#ifndef CMD_UART_H_
#define CMD_UART_H_

#include "stm32l1xx.h"
#include "ch.h"
#include "hal.h"
#include "kl_lib_L15x.h"

// Set to true if RX needed
#define UART_RX_ENABLED     TRUE

// UART
#define UART_TXBUF_SIZE     2700
#define UART                USART2
#define UART_GPIO           GPIOA
#define UART_TX_PIN         2
#define UART_AF             AF7
#define UART_DMA            STM32_DMA1_STREAM7
#define UART_DMA_CHNL       4   // for complex DMA engines. Ignored in case of L MCUs.
#define UART_RCC_ENABLE()   rccEnableUSART2(FALSE)

#define UART_DMA_MODE       STM32_DMA_CR_CHSEL(UART_DMA_CHNL) | \
                            DMA_PRIORITY_LOW | \
                            STM32_DMA_CR_MSIZE_BYTE | \
                            STM32_DMA_CR_PSIZE_BYTE | \
                            STM32_DMA_CR_MINC |       /* Memory pointer increase */ \
                            STM32_DMA_CR_DIR_M2P |    /* Direction is memory to peripheral */ \
                            STM32_DMA_CR_TCIE         /* Enable Transmission Complete IRQ */

#if UART_RX_ENABLED
#define UART_RX_PIN         3
#define UART_RX_REG         UART->DR
#define UART_RX_IRQ_ENABLE() nvicEnableVector(STM32_USART2_NUMBER, CORTEX_PRIORITY_MASK(STM32_SERIAL_USART2_PRIORITY))
#define UART_RX_IRQ         STM32_USART2_HANDLER

#define UART_RXBUF_SZ       2700    // unprocessed bytes
#define UART_CMDDATA_SZ     252     // payload bytes

enum RcvState_t {rsStart, rsCmdCode1, rsCmdCode2, rsData1, rsData2};
#endif

class CmdUart_t {
private:
    uint8_t TXBuf[UART_TXBUF_SIZE];
    char SprintfBuf[UART_TXBUF_SIZE];
    uint8_t *PWrite, *PRead;
    bool IDmaIsIdle;
    uint32_t IFullSlotsCount, ITransSize;
#if UART_RX_ENABLED
    RcvState_t RxState;
    uint8_t IRxBuf[UART_RXBUF_SZ];
    uint8_t CmdCode;
    uint8_t CmdData[UART_CMDDATA_SZ], *PCmdWrite;
#endif
public:
    void Printf(const char *S, ...);
    void FlushTx() { while(!IDmaIsIdle); }  // wait DMA
    void PrintNow(const char *S) {
        while(*S != 0) {
            while(!(UART->SR & USART_SR_TXE));
            UART->DR = *S++;
        }
    }
    void Init(uint32_t ABaudrate);
    void Cmd(uint8_t CmdCode, uint8_t *PData, uint32_t Length) { Printf("#%X,%A\r\n", CmdCode, PData, Length, 0); }

    void IRQDmaTxHandler();
#if UART_RX_ENABLED
    // Inner use
    InputQueue iqueue;
    void IProcessByte(uint8_t b);
    void IResetCmd() { RxState = rsStart; PCmdWrite = CmdData; }
#endif
};

extern CmdUart_t Uart;

#if UART_RX_ENABLED
extern void UartCmdCallback(uint8_t CmdCode, uint8_t *PData, uint32_t Length);
#endif

#endif /* CMD_UART_H_ */
