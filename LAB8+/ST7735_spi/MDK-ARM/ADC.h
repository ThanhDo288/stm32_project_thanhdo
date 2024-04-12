#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void ADC_Init(void);

uint32_t ADC_In(void);

void ADC_Reset(void);

#endif