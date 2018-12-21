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

void CLK_wait(void);
u8 RTCread(void);
void RTCsend_byte(u8 temp);
void IICinit(void);
void IIC_stop(void);

#endif	/* XC_HEADER_TEMPLATE_H */

