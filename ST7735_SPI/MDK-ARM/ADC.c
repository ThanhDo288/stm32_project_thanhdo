#include <stdint.h>
#include "stm32f103xb.h"

void ADC_Init(void) {
	 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  
  // Bu?c 2: C?u hình chân A0 là d?u vào analog
  GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
  GPIOA->CRL |= GPIO_CRL_CNF0_1;
    // Enable ADC1 clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	   // Set ADC prescaler to 6 (ADC clock = 72MHz / 6 = 12MHz)
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	  ADC1->CR2 &= ~ ADC_CR2_ADON;  


 // Configure ADC channel
    ADC1->SQR1 &= ~ADC_SQR1_L_Msk;  // Set regular channel sequence length to 1 ?
    ADC1->SQR3 = 0;                 // Set channel 0 as the first conversion in the sequence

	  // C?u hình các thông s? ADC
 // ADC1->CR1 = 0; // Xóa các cài d?t tru?c dó
  //ADC1->CR1 |= 0x00; // Ğ? phân gi?i 12-bit
  //ADC1->CR2 = 0; // Xóa các cài d?t tru?c dó
  ADC1->CR2 |= ADC_CR2_ADON;  // Enable ADC1

  ADC1->CR2 |= ADC_CR2_SWSTART;

	ADC1->SMPR2 = 0; // Xóa các cài d?t tru?c dó
  ADC1->SMPR2 |= ADC_SMPR2_SMP0_2 ;//| ADC_SMPR2_SMP0_1; // Th?i gian l?y m?u
	
}

uint32_t ADC_In(void) {
    // Start ADC1 conversion

    // Wait for conversion to complete
    while (!(ADC1->SR & ADC_SR_EOC));

    // Read ADC1 value
    uint32_t result = ADC1->DR;

    return result;
}
