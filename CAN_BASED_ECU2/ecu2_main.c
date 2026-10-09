/*Name : Jupalli Karthik
 * ID : INT26001_124
 * Title : CAN based Automotive dashboard (ECU2)
 */
#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern uint8_t lind;
extern uint8_t rind;
extern uint8_t hind;

unsigned char ch = 'O';

void init_config(void)
{
    TRISB = 0x00;
    init_digital_keypad();
    init_adc();
//    init_uart();
    init_can();
}

int main(void)
{
    init_config();
    while (1)
    {
        /* Check indicator/headlight switch */
        IndicatorStatus Indstatus = process_indicator();
        if (Indstatus == e_ind_right)
        {
            if (rind == 1)
            {
                ch = 'R';
                RIGHT_IND_ON();
            }
            else
            {
                ch = 'O';
                RIGHT_IND_OFF();
            }
        }
        else if (Indstatus == e_ind_left)
        {
            if (lind == 1)
            {
                ch = 'L';
                LEFT_IND_ON();
            }
            else
            {
                ch = 'O';
                LEFT_IND_OFF();
            }
        }
        else if (Indstatus == e_head_light)
        {
            if (hind == 1)
            {
                ch = 'H';
                HEAD_LIGHT_ON();
            }
            else
            {
                ch = 'O';
                HEAD_LIGHT_OFF();
            }
        }

        /* Get RPM */
        uint32_t rpm = get_rpm();
        /* Convert ADC 0-1023 to RPM 0-6000 */
        rpm = (rpm * 6000UL) / 1023UL;
        /* Convert RPM to string */
        char rpm_data[5];
        sprintf(rpm_data, "%lu", rpm);
        /* Send RPM through CAN */
        can_transmit(RPM_MSG_ID,(uint8_t *)rpm_data,strlen(rpm_data));
        for(volatile uint16_t delay = 0;delay<500;delay++);
        
        /* Engine temperature */
        uint16_t temp = get_engine_temp();
        char temp_data[4];
        sprintf(temp_data,"%u",temp);
        /* Send temperature through CAN */
        can_transmit(ENG_TEMP_MSG_ID,temp_data,strlen(temp_data));
        /* Send indicator/headlight status */
        for(volatile uint16_t delay = 0;delay<500;delay++);
        can_transmit(INDICATOR_MSG_ID,&ch,1);
        for(volatile uint16_t delay = 0;delay<500;delay++);
    }
}