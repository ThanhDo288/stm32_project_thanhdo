#include <stdint.h>
#include "stm32f10x.h"

void IO_Init(void) {
    // --UUU-- Code to initialize PB4 (connected to the switch) and PB5 (connected to the LED)
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable clock for Port B

    GPIOB->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_MODE4);
    GPIOB->CRL |= GPIO_CRL_CNF5_0; // General purpose push-pull output
    GPIOB->CRL |= GPIO_CRL_CNF4_1; // Input floating

    // Enable pull-up on PB4 (the switch)
    GPIOB->ODR |= GPIO_ODR_ODR4;
}

void IO_HeartBeat(void) {
    // --UUU-- Toggle the state of PB5 (LED)
    GPIOB->ODR ^= GPIO_ODR_ODR5;
}

void IO_Touch(void) {
    // Wait for release (Pin 4 high)
 // --UUU-- Wait for release, delay for 20ms, and then wait for press
    while ((GPIOB->IDR & GPIO_IDR_IDR4) == 0) {}
  

    // Delay for 20ms
    uint32_t delay = 2000;
    while (delay--) {
        volatile int i = 1000;
        while (i--);
    }

    // Wait for press (Pin 4 low)
   while ((GPIOB->IDR & GPIO_IDR_IDR4) != 0) {}
}
