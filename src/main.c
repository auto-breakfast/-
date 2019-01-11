/*
 * File:   main.c
 * Author: User
 *
 * Created on 2018年12月19日, 下午 4:15
 */
#include <xc.h>
#include "defines.h"
//#include <stdio.h>
//#include <stdlib.h>
#include <uart.h>
#include "mydelay.h"
#include "RTC.h"
#include "Seven-segment display.h"
//#pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1H
#pragma config OSC = HSPLL      // OSC->HSPLL ?????? 4*PLL = 10 * 4 = 40MHZ
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
//
//// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)
//
//// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)
//
//// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
//#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
//
//// CONFIG4L





#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
//
//// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)
//
//// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
//#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)
//
//// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)
//
//// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
//
//// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)
//
//// CONFIG7H
#pragma config EBTRB = OFF


//#include <xc.h>

//void OSC_init() // 32MHZ
//{
//    OSCCONbits.IRCF2 = 1;
//    OSCCONbits.IRCF1 = 1;
//    OSCCONbits.IRCF0 = 1;
//    OSCCONbits.SCS1 =0;
//    OSCCONbits.SCS0 =0;
//    while(!OSCCONbits.IOFS); //等待震盪穩定
//    OSCTUNEbits.PLLEN = 1;
//    
//}
void oclillator_initial()  //      Fosc = 40MHz 
{
    OSCCONbits.IOFS=0;        // turn off internal oscillator
    OSCCONbits.SCS0=0;
    OSCCONbits.SCS1=0;        //System Clock Select bits is primary oscillator
}
void main(void) {
    int a = 11;
    int b = 12;
    u8 address,hour,minute;
    u8 str_1[8]={0x01,0x22,0x08,0x04,0x05,0x19,0x02,0x01};
//    u8 str_1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    u8 str[8]={0};
    u8 reciprocal[3]={0};
//    OSC_init();
    delay_ms(2);
    IICinit();
    oclillator_initial();
    initalUART();
//    PR2=253;
//    CCP2CON=0x2C;
//    TRISBbits.RB3=0;
//    T2CON=0x05;
//    CCPR2=0x00;
    
    RTC_write(str_1);
    while(1)
    {
        if(TXFLAG==1)
        {
//            writeuart(uartdata);
            gettime();
            TXFLAG=0;
        }
        RTCread(str);
        hour = (str[2]/16)*10+(str[2]%16);
        minute = (str[1]/16)*10+(str[1]%16);
        Display(hour-time[0],minute-time[1]);
//        delay_ms(10);
        if(hour-time[0]==0&&minute-time[1]&&str[0]-time[2])
        {
            
        }
    }
    return;
}
