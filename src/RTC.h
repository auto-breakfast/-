#ifndef RTC_H
#define	RTC_H

#include "defines.h"

#define RTC_CE      TRISBbits.TRISB2
#define RTC_CLK     TRISBbits.TRISB1
#define RTC_DATA    TRISBbits.TRISB0

#define IIC_CE      PORTBbits.RB2
#define IIC_CLK     PORTBbits.RB1
#define IIC_DATA    PORTBbits.RB0 

#define IIC_read    PORTBbits.RB0

void IIC_start(void);
void IIC_NAck(void);
void CLK_wait(void);
u8 RTCread_byte(void);
void RTCread(u8*);
void RTCsend_byte(u8 temp);
void IICinit(void);
void IIC_stop(void);
void RTC_write(u8*);

#endif	/* XC_HEADER_TEMPLATE_H */

