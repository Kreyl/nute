/*
 * DBG_Unit.h
 *
 *  Created on: 25.11.2012
 *      Author: Stefan
 */

#ifndef DBG_UNIT_H_
#define DBG_UNIT_H_

#include <stdint.h>
#include "UARTClass.h"
#include "tiny_sprintf.h"

#define PRINTF_BUF_SIZE		254

class DBG_Message_Class {
private:
	uint16_t DbgEnableFlag;
public:
  /*  uint16_t  i;
    void Init(void);
    void Task(void);
    void SendData (void);
    */
	void DbgDisable(void){ DbgEnableFlag = 0; }
	void DbgEnable(void){ DbgEnableFlag = 1; }
    void PrintF(const char *fmt, ...);
};

extern UART_Class DbgUART;

#endif /* DBG_UNIT_H_ */