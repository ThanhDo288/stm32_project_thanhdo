#include "IO.h"
#include "stm32f1xx_hal.h"

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
    GPIOB->CRL &= ~(GPIO_CRL_MODE2| GPIO_CRL_CNF2);
    GPIOB->CRL |= GPIO_CRL_MODE2_0;

    // Enable digital function for PB4 and PB2
   GPIOB->CRL |= (GPIO_CRL_CNF4_0 | GPIO_CRL_CNF2_0);
	}

//------------IO_HeartBeat------------
// Toggle the output state of the  LED.
// Input: none
// Output: none
void IO_HeartBeat(void)
	{
		GPIOB->ODR^=GPIO_ODR_ODR2;
	}


//------------IO_Touch------------
// wait for release and touch of the switch
// Delay to debounce the switch
// Input: none
// Output: none
void IO_Touch(void)
	{
	    // Wait for release (PA0 high)
    while (!(GPIOB->IDR & GPIO_IDR_IDR4)) {}
			Wait10ms(100);
    // Wait for press (PA0 low)
    while (GPIOB->IDR & GPIO_IDR_IDR4) {}
	}

void Wait10ms(uint32_t count){
  uint32_t i;
  for(i=0; i <count*32000; i++){}
}
