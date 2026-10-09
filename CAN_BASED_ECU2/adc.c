#include "adc.h"

void init_adc(void) {
    /*ADCON0*/
    ADON = 0;
    /*ADCON1*/
    /*Selecting channel pins as analog or digital*/
    PCFG0 = 0;
    PCFG1 = 0;
    PCFG2 = 0;
    PCFG3 = 0;
    /*Reference voltage*/
    VCFG0 = 0;
    VCFG1 = 0;
    /*ADCON2*/
    /*Clock source fosc/32 1TAD = 1.6micro*/
    ADCS0 = 0;
    ADCS1 = 1;
    ADCS2 = 0;
    /*Acquisition Time = 4TAD = 4x1.6micro = 6.4microseconds for 1 conversion*/
    ACQT0 = 0;
    ACQT1 = 1;
    ACQT2 = 0;
    /*Right Justification Result format*/
    ADFM = 1;
    /*Turning on th adc*/
    ADON = 1;
}

uint16_t read_adc(uint8_t channel) {
    /*Selecting the channel based on input*/
    ADCON0 = (ADCON0 & 0xC3) | (channel << 2);
    /*To start the conversion*/
    GO = 1;
    /*Checking whether conversion is done or not if done microcontroller will set GO bit to zero*/
    while (GO);
    /*The result will be stored in ADRESH and ADRESL registers it is right justification*/
    return (ADRESH << 8) | ADRESL;
}
