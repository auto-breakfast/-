/*
 * File:   PWM.c
 * Author: user
 *
 * Created on 2018年12月14日, 上午 9:58
 */


#include <xc.h>

void initalPWM(void) {
    
    TRISBbits.RB3=0;
    CCP2CON=0x2C;
    PR2=253;
    T2CON=0x05;
    CCPR2=0x00;
    
}
