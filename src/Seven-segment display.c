/*
 * File:   Seven-segment display.c
 * Author: User
 *
 * Created on 2018年12月7日, 上午 9:53
 */


#include "mydelay.h"
#include "Seven-segment display.h"
#include "defines.h"
void Display(u8 hour,u8 minute)
{
    int row;
    int i=0;
    TRISD = 0x00;
    TRISC &= 0x10;
    u8 str[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6C,0x7C,0x07,0x7F,0x6F};
    for (i=0;i<4;i++)
    {
        switch(i) {
            case 0:
                LATCbits.LATC3 = 1;
                LATCbits.LATC0 = 0;
                LATD = ~str[hour/10];
                break;
            case 1:
                LATCbits.LATC2 = 1;
                LATCbits.LATC3 = 0;
                LATD = ~str[hour%10];
                break;
            case 2:
                LATCbits.LATC1 = 1;
                LATCbits.LATC2 = 0;
                LATD = ~str[minute/10];
                break;
            case 3:
                LATCbits.LATC0 = 1;
                LATCbits.LATC1 = 0;
                LATD = ~str[minute%10];
                break;
            default:
                break;
        }
        LATCbits.LATC0 = 0;
                    
    }
}
