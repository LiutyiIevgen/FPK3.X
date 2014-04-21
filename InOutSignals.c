#include <xc.h>
#include "InOutSignals.h"

char outputBuffer = 0;

unsigned char ReadInSignals()
{
    TRISD = 0x00FF;//set input on RD0-7
    return ~(char)PORTD;
}

void WriteOutSignals(char maska, char data)
{
    maska = ~maska;
    outputBuffer &= maska;
    outputBuffer |= data;
    int outputData = ((~outputBuffer) << 8);
    TRISB = 0x00FF; //set out RB
    PORTB = outputData;
}

unsigned char ReadOutSignals()
{
    return outputBuffer;
}
