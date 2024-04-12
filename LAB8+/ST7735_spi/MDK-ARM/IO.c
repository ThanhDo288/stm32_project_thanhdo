#include "IO.h"
#include "SysTick.h"
#include <stdint.h>
#include "stm32f10x.h"

// PA0: switch
// PA1: LED
void IO_Init(void){
	 // Enable GPIO Port B clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Delay to ensure GPIO Port B clock is enabled
    volatile uint32_t delay = RCC->APB2ENR;

    // Configure PB4 as input
    GPIOB->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
    GPIOB->CRL |= GPIO_CRL_CNF4_1;

    // Enable pull-up resistor for PB4
    GPIOB->ODR |= GPIO_ODR_ODR4;

	
	
    // Configure PB2 as output
    GPIOB->CRL &= ~(GPIO_CRL_MODE6| GPIO_CRL_CNF6);
    GPIOB->CRL |= GPIO_CRL_MODE6_0;

    // Enable digital function for PB4 and PB2
   //GPIOB->CRL |= (GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0//);
	}

void IO_HeartBeat(void){
	GPIOB->ODR = 0x40;
}

void IO_Touch(void){
	while(!((GPIOB->IDR) & GPIO_IDR_IDR4)){}
	SysTick_Wait10ms(100);
	while(GPIOB->IDR  & 0x10){}
}