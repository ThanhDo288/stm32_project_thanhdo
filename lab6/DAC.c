#include <stdint.h>
#include "stm32f10x.h"
#include "DAC.h"

void DAC_Init(void){
		uint32_t delay;
	 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	 GPIOA->CRL  &= ~ (GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE3 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5);  // Ðat chân 0-5 thành dau ra chung
   GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | GPIO_CRL_CNF2 | GPIO_CRL_CNF3 | GPIO_CRL_CNF4 | GPIO_CRL_CNF5);  // Ch?n ch? d? d?u ra t?ng h?p cho chân 0-5
	 GPIOA->CRL  |=  (GPIO_CRL_MODE0_0 | GPIO_CRL_MODE1_0 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE3_0 | GPIO_CRL_MODE4_0 | GPIO_CRL_MODE5_0);  // Ðat chân 0-5 thành dau ra chung

	}
void DAC_Out(uint32_t data){
  // used in Lab 6 and lab 10
	 GPIOA->ODR = (data & 0x3F);
	
}