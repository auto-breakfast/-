#ifndef _UART_H
#define _UART_H
#include <xc.h>
extern char uartdataBuffer[256];
extern unsigned char uartdataCounter;

void initalUART(void);
void writeUARTByte(unsigned char data);
void writeUARTString(unsigned char *data, unsigned char length);

#endif