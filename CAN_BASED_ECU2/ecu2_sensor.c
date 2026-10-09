#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
uint8_t rind = 0;
uint8_t lind = 0;
uint8_t hind = 0;

uint16_t get_rpm() {
    return read_adc(CH4);
}

uint16_t get_engine_temp() {
    //Implement the engine temperature function
    float temp = read_adc(CH6);
//    temp = ((temp * 0.00488)*1000);
    float volt = ((float)temp * 0.00488);
    temp = volt * 1000;
    return (temp/10);
//    return ((temp * 0.00488)*1000)/10;
}
/*Depends on switch press controlling the leds like considering indicators left and right and head light*/
IndicatorStatus process_indicator() {
    uint8_t key = read_digital_keypad(EDGE);
    if (key == SW2) {
        LEFT_IND_OFF();
        rind = !rind;
        return e_ind_right;
    } else if (key == SW1) {
        RIGHT_IND_OFF();
        lind = !lind;
        return e_ind_left;
    } else if (key == SW3) {
        LEFT_IND_OFF();
        RIGHT_IND_OFF();
        hind = !hind;
        return e_head_light;
    }
    return e_ind_off;
}