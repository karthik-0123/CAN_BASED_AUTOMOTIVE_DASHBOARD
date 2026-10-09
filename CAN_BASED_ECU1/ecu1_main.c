/*Name : Jupalli Karthik
 * ID : INT26001_124
 * Title : CAN based Automotive dashboard (ECU1)
 */
#include "adc.h" //To calculate the speed
#include <stdio.h>
#include <string.h>
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "timer0.h"//To make the buzzer sound for 3 sec after collision
void init_external_interrupt0(void);

/*Whenever collision is happened by using external interrupt source it will come to Gear neutral*/
void init_external_interrupt0(void) {
    /*Enabling the interrupts*/
    GIE = 1;
    PEIE = 1;
    /*Interrupt enable bit*/
    INT0IE = 1;
    /*Interrupt flag bit*/
    INT0IF = 0;
    /*When the switch is */
    /*for clock edge is Rising*/
    INTEDG0 = 1;
}

void init_config() {
    init_digital_keypad(); //Digital keypad for gear up ,gear down ,collision and reverse
    init_adc(); //To calculate the speed through potentiometer
    //Buzzer configuration - whenever collision occurs the buzzer should be on for 3 sec 
    TRISE0 = 0;
    RE0 = 0;
    init_can();
    //External interrupt -> after collision making it to Gear neutral 
    init_external_interrupt0();
    //To calculate 3 secs of time after collision to make the buzzer sound
    init_timer0();
}
/*Gears array of strings*/
unsigned char *gears[8] = {"GN", "G1", "G2", "G3", "G4", "G5", "GR", "CO"};
/*To calculate the sec*/
extern uint8_t sec;

int main() {
    init_config();
    while (1) {
        /*Reading the gear position using digital key pad*/
        unsigned char gpos = get_gear_pos();
        /*From adc reading the speed*/
        uint16_t speed = get_speed();
        /*To reduce the values 0 - 1023 to 0 - 100*/
        speed = (speed * 20) / 1023;
        /*If it is collision 3 seconds then timer should be off and buzzer should be off */
        if (gpos == 7) {
            TMR0ON = 1;
            speed = 0;
            if (sec > 3) {
                TMR0ON = 0;
                RE0 = 0;
            }
        } else if (gpos == 6 || gpos == 1) {
            speed = speed;
        }/*This is to limit the speed*/ 
        else if (gpos == 2) {
            speed = 20 + speed;
        } else if (gpos == 3) {
            speed = 40 + speed;
        } else if (gpos == 4) {
            speed = 60 + speed;
        } else if (gpos == 5) {
            speed = 80 + speed;
        } else if (gpos == 0) {
            speed = 0;
        }
        char gspeed[4];
        sprintf(gspeed, "%d", speed);
        /*Transmitting the message through can protocol (SPEED)*/
        can_transmit(SPEED_MSG_ID,gspeed,strlen(gspeed));
        for(volatile uint16_t delay = 0;delay<2000;delay++);
        /*Transmitting the message through can protocol (GEAR POS)*/
        can_transmit(GEAR_MSG_ID,gears[gpos],2);
    }
}
