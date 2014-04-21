/**
 * @author Kyrylov Andrii
 * @todo init timer 1 interrupt (write to lcd)
 */

void StartTimer1()// clear WDT
{
    // Configure Timer 1.
    // PR3 and TCKPS are set to call interrupt every 500ms.
    // Period = PR3 * prescaler * Tcy = 58594 * 256 * 33.33ns = 500ms
    T1CON = 0;            // Clear Timer 1 configuration
    T1CONbits.TCKPS = 3;  // Set timer 1 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
    PR1 = 60000;          // Set Timer 1 period (max value is 65535)
    _T1IP = 0x1;            // Set Timer 1 interrupt priority
    _T1IF = 0;            // Clear Timer 1 interrupt flag
    _T1IE = 1;            // Enable Timer 1 interrupt
    T1CONbits.TON = 1;    // Turn on Timer 1
}

void StartTimer4()// write to can bus
{
    // Configure Timer 3.
    // PR3 and TCKPS are set to call interrupt every 500ms.
    // Period = PR3 * prescaler * Tcy = 58594 * 256 * 33.33ns = 500ms
    T4CON = 0;            // Clear Timer 2 configuration
    T4CONbits.TCKPS = 3;  // Set timer 3 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
    PR4 = 1250;          // Set Timer 3 period (max value is 65535)
    _T4IP = 0x3;            // Set Timer 3 interrupt priority
    _T4IF = 0;            // Clear Timer 3 interrupt flag
    _T4IE = 1;            // Enable Timer 3 interrupt
    T4CONbits.TON = 1;    // Turn on Timer 3
}