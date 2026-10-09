
#ifndef ADC_H
#define	ADC_H
#include <xc.h>
#include<stdint.h>

#define CH0     0
#define CH1     1
#define CH2     2
#define CH3     3
#define CH4     4
#define CH5     5
#define CH6     6
#define CH7     7
#define CH8     8
#define CH9     9
#define CH10    10

void init_adc(void);

uint16_t read_adc(uint8_t channel);

#endif	/* ADC_H */

