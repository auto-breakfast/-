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
    u8 row;
    TRISD = 0x00;
    TRISC &= 0x10;
    u8 str[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6C,0x7C,0x07,0x7F,0x6F};
    
    for (int i=0;i<4;i++)
    {
        switch(i) {
            case 0:
                LATD = str[hour/10];
                break;
            case 1:
                LATD = str[hour%10];
                break;
            case 2:
                LATD = str[minute/10];
                break;
            case 3:
                LATD = str[minute%10];
                break;
            default:
                break;
        }
                    
    }
}
