#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
//#include "uart.h"

/*To check the gear position*/
unsigned char gear_pos = 0;

/*Considering potentiometer as a speed and calculating through adc*/
uint16_t get_speed() {
    return read_adc(CH4);
}
/*Count for to calculate the overflows*/
uint16_t count = 0;
/*To count the seconds*/
uint8_t sec = 0;
uint8_t gr_flag = 0;

/*ISR function*/
void __interrupt() isr(void) {
    /*For external interrupt*/
    if (INT0IF == 1) {
        INT0IF = 0;
        /*Turning off the timer and reseting all the position and other values*/
        TMR0ON = 0;
        sec = 0;
        count = 0;
        gear_pos = 0;
    }
    /*For timer0*/
    if (TMR0IF == 1) {
        TMR0IF = 0;
        TMR0 = TMR0 + 8;
        /*Like generating PWM to reduce the buzzer sound for 50% .*/
        count++;
        if (count < 5000) {
            RE0 = 1;
        } else if (count < 10000) {
            RE0 = 0;
        } else if (count < 15000) {
            RE0 = 1;
        } else if (count < 20000) {
            RE0 = 0;
        } else {
            count = 0;
            sec++;
        }
    }
}

unsigned char get_gear_pos() {
    /*To implement the gear up, gear down ,collision and reverse gear using digital keypad with edge triggering*/
    unsigned char key = read_digital_keypad(EDGE);
    /*SW1 -> Increment the gear*/
    if (key == SW1) {
        if (gear_pos < 5) {
            gear_pos++;
        }
    }/*SW2 ->decrement the gear*/
    else if (key == SW2) {
        if (gear_pos > 0 && gear_pos <= 5) {
            gear_pos--;
        }
    }/*SW3 ->making collision*/
    else if (key == SW3) {
        gear_pos = 7;
        TMR0ON = 1;
    }/*SW4 -> For the reverse gear*/
    else if (key == SW4 && gear_pos != 7) {
        if (gr_flag == 0) {
            gear_pos = 6;
            gr_flag = 1;
        } else {
            gr_flag = 0;
            gear_pos = 0;
        }
    }
    return gear_pos;
}

