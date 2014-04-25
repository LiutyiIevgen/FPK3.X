/* 
 * File:   main.c
 * Author: andrey
 *
 * Created on 30 ?????? 2013, 9:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>

#include "globals.h"
#include "MainLibrary.h"
#include "Timer.h"
#include "Can.h"
#include "PathComands.h"
#include "InOutSignals.h"

// FOSC
#pragma config FOSFPR = XT_PLL16             // Oscillator (XT)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512      // WDT Prescaler A (1:512)
#pragma config WDT = WDT_ON            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV_45            // Brown Out Voltage (4.5)
#pragma config BOREN = PBOR_OFF         // PBOR Enable (Disable)
#pragma config MCLRE = MCLR_EN         // Master Clear Enable (Enable)

// FBS
#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF            // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

unsigned int maj_i = 0;

//clear WDT timer
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);
//write to can bus
void __attribute__((__interrupt__, __auto_psv__)) _T4Interrupt(void);
// Can Receive Parameter
void __attribute__ ((__interrupt__, __auto_psv__)) _C1Interrupt (void);

int main(int argc, char** argv) {
    ADPCFG = 0xFFFF;//RA only digit
    ClrWdt();
    //StartTimer1();// start timer for WDT clearing
    Can1Initialization();
    StartTimer4();
    //TurnOnRelay();

    while(1)
    {
        ClrWdt();
        delay(1000000);
    }
    return (EXIT_SUCCESS);
}
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void)
{
    // Clear Timer 1 interrupt flag
    _T1IF = 0;
    
}
void __attribute__((__interrupt__, __auto_psv__)) _T4Interrupt(void)
{
    // Clear Timer 4 interrupt flag
    // Write to can bus
    _T4IF = 0;
    char relayData[8] = {0,0,0,0,0,0,0,0};
    relayData[0] = ~ReadInSignals();
    relayData[1] = ~ReadOutSignals();
    unsigned int sId;
    sId = 0x480;
    sId += _nodeId;
    Can1SendData(sId, relayData, 2);
}
void __attribute__ ((__interrupt__, __auto_psv__)) _C1Interrupt (void){
    IFS1bits.C1IF = 0; //Clear CAN1 interrupt flag
    C1INTFbits.RX0IF = 0; //Clear CAN1 RX interrupt flag
    char rxData[8];
    if(C1CTRLbits.ICODE == 7) //check filters
    {
        C1INTFbits.WAKIF = 0;
        return;
    }
    unsigned int sId = C1RX0SIDbits.SID;
    Can1ReceiveData(rxData);
    WriteOutSignals(0b11111111, rxData[3]);
    C1RX0CONbits.RXFUL = 0;
  }
