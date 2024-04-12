#include <stdint.h>
#include "stm32f10x.h"
#include "Key.h"

void Key_Init(void){
	  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    // C?u hình chân d?u vào PB3-PB0
    GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | GPIO_CRL_CNF2 | GPIO_CRL_CNF3);
    GPIOB->CRL &=~ (GPIO_CRL_MODE0_0 | GPIO_CRL_MODE1_0 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE3_0);
    

}
uint32_t Key_In(void){
// write this
return  GPIOB->IDR& 0x0F; // replace this line

}
