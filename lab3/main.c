#include <stdint.h>
#include "stm32f10x.h"
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
#define start 3
#define change 2
void PortInit( void ){
	
	// Initialize GPIO ports 
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ; // PortA,PortB,PortC
	
	// set A0,A1 as switches
	GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0 | GPIO_CRL_MODE1 | GPIO_CRL_CNF1 ) ;
	GPIOA->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 ; // pull up mode
	
	// set B8 light output
	GPIOB->CRH &= ~(GPIO_CRH_MODE8|GPIO_CRH_CNF8 );
	GPIOB->CRH |= GPIO_CRH_MODE8_0;	
}
uint32_t dutycycle=start;
void IO_Touch(void) {
    // Wait for release (PA0 high)
    while (!(GPIOA->IDR & GPIO_IDR_IDR0)) {}
			SysTick_Wait100ms(start);
    // Wait for press (PA0 low)
    while (GPIOA->IDR & GPIO_IDR_IDR0) {}
}
void IO_HeartBeat(void) {
    // Toggle the output state of Pin 9 (LED)
    GPIOB->ODR ^= GPIO_ODR_ODR8;
}

int main(void){
	SysTick_Init();
	PortInit();
	// change perious light
	GPIOB->ODR = GPIO_ODR_ODR8;
}