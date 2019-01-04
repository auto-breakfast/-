/*
 * File:   uart.c
 * Author: user
 *
 * Created on 2018年12月7日, 上午 9:39
 */
#include <xc.h>
int lenght=0,TXFLAG=0;
char uartdata[30]={0};
int time[3]={0};

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
        uartdata[lenght++]=RCREG;
        
        if(lenght == 8 || RCREG == 0){
            lenght=0;
            TXFLAG=1;
        }
    }
    PIR1bits.RCIF=0;
//    TXFLAG=1;
}

void writeuart(unsigned char *data){
    int i=0;
    while(data[i]!='\0'){
        while(!TRMT);
        TXREG=data[i];
        i++;
    }
}

void gettime(){
    if(uartdata[2] != ':' || uartdata[5] != ':'){
//        uartdata=(void*)"error";
        uartdata[0]='e';
        uartdata[1]='r';
        uartdata[2]='r';
        uartdata[3]='o';
        uartdata[4]='r';
        uartdata[5]='\0';
        lenght=0;
        writeuart(uartdata);
    }
    else{
//        uartdata=(void *)"ok";
//        uartdata[9]='o';
//        uartdata[10]='k';
//        uartdata[11]='\0';
//        lenght=0;
        writeuart(uartdata);
        
        time[0]=((int)uartdata[0]-48)*10+((int)uartdata[1]-48);
        time[1]=((int)uartdata[3]-48)*10+((int)uartdata[4]-48);
        time[2]=((int)uartdata[6]-48)*10+((int)uartdata[7]-48);
        
        if(time[0] > 24 || time[1] > 60 || time[2] > 60){
            uartdata[0]='e';
            uartdata[1]='r';
            uartdata[2]='r';
            uartdata[3]='o';
            uartdata[4]='r';
            uartdata[5]='\0';
            lenght=0;
            writeuart(uartdata);
        }
        else{
            uartdata[0]='o';
            uartdata[1]='k';
            uartdata[2]='\0';
            lenght=0;
            writeuart(uartdata);
        }
    }
}
