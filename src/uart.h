#ifndef _UART_H
#define _UART_H
#include <xc.h>
extern char uartdataBuffer[30];
extern int i;

void initalUART(void);
void interrupt UART(void);

#endif