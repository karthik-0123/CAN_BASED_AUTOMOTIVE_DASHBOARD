
#include<xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void) {
    /*Treating last 4 bits of PORTC as input*/
    TRISC = TRISC | 0x0F;
}

uint8_t read_digital_keypad(uint8_t trigger) {
    /*For edge triggering to trace the previous value*/
    static uint8_t flag = 1;
    /*If triggering is level*/
    if (trigger == LEVEL) {
        return PORTC & 0x0F;

    }/*If triggering is edge*/
    else if (trigger == EDGE) {
        if (((PORTC & 0x0F) != ALL_RELEASED) && flag == 1) {
            flag = 0;
            return PORTC & 0x0F;
        } else if ((PORTC & 0x0F) == ALL_RELEASED) {
            flag = 1;
        }
        return ALL_RELEASED;
    }
}