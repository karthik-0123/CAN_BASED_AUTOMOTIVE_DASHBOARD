#ifndef DIGITAL_KEYPAD_H
#define	DIGITAL_KEYPAD_H
#include<stdint.h>

/*Trigger macros*/
#define LEVEL 1
#define EDGE 0

/*Switches macros*/
#define SW1 0x0E
#define SW2 0x0D
#define SW3 0x0B
#define SW4 0x07
#define ALL_RELEASED 0x0F

/*To initialize the digital keypad*/
void init_digital_keypad(void);

/*To read the digit keypad*/
uint8_t read_digital_keypad(uint8_t trigger);

#endif

