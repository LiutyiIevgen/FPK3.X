#include <xc.h>
#include "PathComands.h"

void TurnOnOrOffRelay(char data)
{
    data = ~data;
    TRISBbits.TRISB8 = 0;//set output on RB8
    TRISBbits.TRISB9 = 0;//set output on RB8
    TRISBbits.TRISB10 = 0;//set output on RB8
    TRISBbits.TRISB11 = 0;//set output on RB8
    TRISBbits.TRISB12 = 0;//set output on RB8
    TRISBbits.TRISB13 = 0;//set output on RB8
    TRISBbits.TRISB14 = 0;//set output on RB8
    TRISBbits.TRISB15 = 0;//set output on RB8

    LATBbits.LATB8 = data&1; data>>=1;
    LATBbits.LATB9 = data&1; data>>=1;
    LATBbits.LATB10 = data&1; data>>=1;
    LATBbits.LATB11 = data&1; data>>=1;
    LATBbits.LATB12 = data&1; data>>=1;
    LATBbits.LATB13 = data&1; data>>=1;
    LATBbits.LATB14 = data&1; data>>=1;
    LATBbits.LATB15 = data&1; data>>=1;
}