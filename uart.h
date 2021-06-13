
#ifndef UART_H_
#define UART_H_

#include "tm4c123gh6pm.h"
# include "common_macros.h"
#include "std_types.h"

void UART1_init(void);

uint8_t UART1_getByte(void);

void UART1_sendByte(uint8_t data);


#endif