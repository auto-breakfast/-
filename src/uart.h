#ifndef _UART_H
#define _UART_H
#include <xc.h>
extern char uartdata[30];
extern int i,TXFLAG;

void initalUART(void);
void interrupt UART(void);
void writeuart(unsigned char *data);

#endif