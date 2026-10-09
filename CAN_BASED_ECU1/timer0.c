
#include "timer0.h"
void init_timer0(void) {

    /*To configure the timer*/
    /*Starting with value 6 because per second interrupts occuring and extra .25
     *  for 1 second 19531.25 interrupts will occur  so by starting with 6 we can calculate approximately so we will get 20000*/
    TMR0 = 6;
    /*Timer 0 On*/
    TMR0ON = 0;
    /*8-bit Timer*/
    T08BIT = 1;
    /*Clock soure internal*/
    T0CS = 0;
    /*Disable prescale*/
    PSA = 1;
    /*making timer0 as interrupt source*/
    /*Enabling global interrupt*/
    GIE = 1;
    /*Peripheral Interrupt*/
    PEIE = 1;
    /*Enabling the timer0 as a interrupt*/
    TMR0IE = 1;
    /*Clearing the flag it will be set by microcontroller*/
    TMR0IF = 0;

}
