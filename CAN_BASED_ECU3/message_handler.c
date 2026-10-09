#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


volatile unsigned char led_state = LED_OFF, status = e_ind_off;

void handle_speed_data(uint8_t *data, uint8_t len) {
    clcd_putch(' ',LINE1(3));
    clcd_putch(' ',LINE1(4));
    clcd_putch(' ',LINE1(5));
    clcd_print(data, LINE1(3));
}

void handle_gear_data(uint8_t *data, uint8_t len) {
    clcd_putch(' ',LINE1(9));
    clcd_putch(' ',LINE1(10));
    clcd_putch(' ',LINE1(11));
    clcd_print(data, LINE1(9));
}

void handle_indicator_data(uint8_t *data, uint8_t len) {

    clcd_print(data, LINE1(14));
    if (data[0] == 'H') {
        LEFT_IND_OFF();
        RIGHT_IND_OFF();
        HEAD_LIGHT_ON();
    } else if (data[0] == 'L') {
        HEAD_LIGHT_OFF();
        RIGHT_IND_OFF();
        LEFT_IND_ON();
    } else if (data[0] == 'R') {
        HEAD_LIGHT_OFF();
        LEFT_IND_OFF();
        RIGHT_IND_ON();
    } else {
        HEAD_LIGHT_OFF();
        LEFT_IND_OFF();
        RIGHT_IND_OFF();
    }
    clcd_putch(' ',LINE1(15));
}

void handle_rpm_data(uint8_t *data, uint8_t len) {

    clcd_print(data, LINE2(2));
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) {

    clcd_print(data, LINE2(10));
    clcd_putch('C', LINE2(13));
}

void process_canbus_data() {
    uint16_t msg_id;
    uint8_t data[9];
    uint8_t len;
    can_receive(&msg_id, data, &len);
    //    clcd_print(data,LINE1(0));
    if (len > 0 && len <= 8) {
        data[len] = '\0';
        switch (msg_id) {
            case SPEED_MSG_ID:
                handle_speed_data(data, len);
                break;
            case GEAR_MSG_ID:
                handle_gear_data(data, len);
                break;
            case RPM_MSG_ID:
                handle_rpm_data(data, len);
                break;
            case INDICATOR_MSG_ID:
                handle_indicator_data(data, len);
                break;
            case ENG_TEMP_MSG_ID :
                handle_engine_temp_data(data,len);
                break;
        }
    }
}