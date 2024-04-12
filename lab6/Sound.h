#ifndef __Sound_h_
#define __Sound_h_
#include <stdint.h>

void Key_Init(void);
uint32_t Key_In(void);
void Sound_Init(void);
void Sound_Start(uint32_t period);
void SysTick_Handler(void);
#endif