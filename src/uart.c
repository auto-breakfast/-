/*
 * File:   uart.c
 * Author: user
 *
 * Created on 2018年12月7日, 上午 9:39
 */
#include <xc.h>
extern int i=0,TXFLAG=0;
extern char uartdata[30] = {0};

void initalUART(void) {
    TRISC=0x00;
    TRISCbits.RC6=1;
    TRISCbits.RC7=1;
    
    TXSTA=0x00;
    TXSTAbits.TX9=0;//9bit
    TXSTAbits.TXEN=1;//TX開啟
    TXSTAbits.SYNC=0;//模式選擇 0為異步 1為同步
    TXSTAbits.SENDB=0;
    TXSTAbits.BRGH=0;//鮑率選擇
    TXSTAbits.TX9D=0;
    
    RCSTA=0x00;
    RCSTAbits.RX9=0;
    RCSTAbits.CREN=1;
    RCSTAbits.FERR=0;
    RCSTAbits.OERR=0;
    RCSTAbits.RX9D=0;
    RCSTAbits.SPEN=1;//開
    
    BAUDCON=0x00;
    BAUDCONbits.ABDOVF=0;
    BAUDCONbits.BRG16=0;
    
    SPBRG=64;
    
    //PIE1bits.RCIE=0;
    RCONbits.IPEN=1;                    // turn off priority level
    PIE1bits.TX1IE=0;                   //turn off TX interrupt
    PIE1bits.RCIE=1;                    //enable RX interrupt
    INTCONbits.GIE=1;                   // Peripheral Interrupt disEnable bit
    INTCONbits.PEIE=1;                  // Global Interrupt Enable bit
    
}

void interrupt UART(){
    if(PIR1bits.RCIF){
        uartdata[i++]=RCREG;
    }
    PIR1bits.RCIF=0;
    i=0;
    TXFLAG=1;
}

void writeuart(unsigned char *data){
    int j=0;
    while(data[j]!='\0'){
        while(!TRMT);
        TXREG=data[j];
        j++;
    }
}



