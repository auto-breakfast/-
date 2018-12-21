#ifndef _UART_H
#define _UART_H
#include <xc.h>
extern char uartdata[30]={0};
extern int lenght,TXFLAG;

void initalUART(void);
void interrupt UART(void);
void writeuart(unsigned char *data);
void gettime(void);


#endif