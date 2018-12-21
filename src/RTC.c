/*
 * File:   IIC.c
 * Author: User
 *
 * Created on 2018年12月14日, 上午 10:50
 */

#include "RTC.h"
#include "mydelay.h"
void CLK_wait(void)
{
    IIC_CLK = 1;
    delay_us(2);
    IIC_CLK = 0;
    delay_us(2);
}
void IICinit(void)
{
    RTC_CE = 0;
    RTC_CLK = 0;
    RTC_DATA = 0;
    IIC_CE = 0;
    IIC_CLK = 0;
    IIC_DATA = 0;
}

void IIC_stop(void);
u8 RTCread(void) {
    RTC_DATA = 1;
    IIC_CE = 1;
    u8 t,time=0;
    for(t=0;t<8;t++)
    {
        IIC_CLK = 1;
        delay_us(2);
        time<<=1;
        if(IIC_DATA)
            time+=1;
        IIC_CLK = 0;
        delay_us(2);
    }
    IIC_CE = 0;
    RTC_DATA = 0;
    return time;
}
void RTCsend_byte(u8 temp)
{
    IIC_CE = 1;
    u8 t = 0;
    for(t=0;t<8;t++)
    {
        if(temp&0x80)
            IIC_DATA = 1;
        else
            IIC_DATA = 0;
        temp<<=1;
        CLK_wait();
    }
    IIC_CE =0;
}
