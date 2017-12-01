
#ifndef __UART_H
#define __UART_H

#include "stm32f4xx.h"

void com1_config(void);
void com1_putc(uint8_t ch);
void com1_puts(char *ch);


#endif /* __UART_H */

