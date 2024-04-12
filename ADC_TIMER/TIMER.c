#include <stdint.h>
#include "stm32f10x.h"
void Timer2_Register(void)
{
	
	// enable clock for timer2
	RCC->APB1ENR|=0x01;
	// TMx auto-reload-register
	TIM2->ARR = 1000;
	// PSC[15:0] : chia tan
	TIM2->PSC=72-1;// chia tu 72Mhz thanh 72/72=1Mhz
	TIM2->CR1= 0x01;// bit 0 cen: dem len
	//reload lai cac cai dat phia tren de timer chay dung
	TIM2->EGR= 0x01;
} 