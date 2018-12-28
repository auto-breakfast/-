/*
 * File:   IIC.c
 * Author: User
 *
 * Created on 2018年12月14日, 上午 10:50
 */

#include "RTC.h"
#include "mydelay.h"
void IIC_start(void)
{
    IIC_CE = 1;
    IIC_DATA = 1;
//    delay_us(1);
    IIC_DATA = 0;
}
void IIC_NAck(void)
{
	IIC_CLK = 0;
	RTC_DATA = 0;
	IIC_DATA = 1;
	delay_us(1);
	IIC_CLK = 1;
	delay_us(1);
	IIC_CLK = 0;
}
void CLK_wait(void)
{
    IIC_CLK = 1;
    delay_us(1);
    IIC_DATA = 0;
    IIC_CLK = 0;
    delay_us(1);
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

void IIC_stop(void)
{
    IIC_DATA = 0;
    IIC_DATA = 1;
    delay_us(1);
    IIC_CE = 0;
    IIC_DATA = 0;
    
}
u8 RTCread_byte(void)
{
    u8 time = 0;
    IIC_CE = 1;
    for(u8 i=0;i<8;i++)
    {
        if(IIC_DATA == 1)
            time++;
        time<<=1;
        IIC_CLK = 1;
        delay_us(1);
        IIC_CLK = 0;
        delay_us(2);
    }
    IIC_CE = 0;
    return time;
}
void RTCread(u8*str) {
    IIC_start();
    RTCsend_byte(0xBF);
    IIC_CE = 0;
    RTC_DATA = 1;
    u8 t;
    IIC_CE =1;
    for(t=0;t<8;t++)
    {
        *(str+t)=RTCread_byte();
    }
//    IIC_CE =0;
    RTC_DATA = 0;
    IIC_stop();
}
void RTCsend_byte(u8 temp)
{
    IIC_CE = 1;
    u8 t = 0;
    for(t=0;t<8;t++)
    {
        if(temp&0x01)
            IIC_DATA = 1;
        else
            IIC_DATA = 0;
        temp>>=1;
        CLK_wait();
    }
//    IIC_NAck();
    IIC_DATA = 0;
//    IIC_CE =0;
}
void RTC_write(u8*str_1)
{
    u8 order[8]={0x80,0x82,0x84,0x86,0x8A,0x8C,0x8E,0x90};
    IIC_start();
    for(u8 t=0;t<8;t++)
    {
        RTCsend_byte(order[t]);
        RTCsend_byte(*(str_1+t));
        IIC_CE = 0;
    }
    IIC_stop();
}