#ifndef __DAC_h_
#define __DAC_h_
#include <stdint.h>

// Initialize SysTick with busy wait ruuning at bus clock

void DAC_Init(void);

// Time delay using busy wait
// The delay parameter is in units of the core clock
void DAC_Out(uint32_t data);
#endif