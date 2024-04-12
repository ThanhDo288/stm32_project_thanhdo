#include <stdint.h>
#include "stm32f10x.h"
#include "SysTick.h"

// Initialize SysTick with bus wait at bus clock

void SysTick_Wait(uint32_t period) {
    SysTick->CTRL = 0;
    SysTick->LOAD = period - 1;  // Ð?t giá tr? thanh ghi LOAD d? xác d?nh chu k? th?i gian
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE | SysTick_CTRL_CLKSOURCE /*| SysTick_CTRL_TICKINT */;
		//while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0) {}
}



void SysTick_Wait100ms(uint32_t delay){
	uint32_t i;
	for(i = 0; i < delay; i++){
		SysTick_Wait(800000); // wait 100ms
	}
}