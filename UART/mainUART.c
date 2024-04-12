#include <stdint.h>
#include "stm32f10x.h"
#include "UART.h"
#include "PLL.h"
void PortB_Init(void) {
    // K�ch ho?t clock cho c?ng GPIO Port B
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // C?u h�nh c�c ch�n GPIO PB1, PB2 v� PB3 nhu d?u ra (output)
    GPIOB->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1 | GPIO_CRL_CNF2 | GPIO_CRL_MODE2 | GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
    GPIOB->CRL |= GPIO_CRL_MODE1_0 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE3_0;

    // C?u h�nh Pull-up cho ch�n GPIO PB4
    GPIOB->ODR |= GPIO_ODR_ODR4;

    // K�ch ho?t ch?c nang digital cho c�c ch�n GPIO PB1, PB2, PB3 v� PB4
    GPIOB->CRL |= GPIO_CRL_CNF1_0 | GPIO_CRL_CNF2_0 | GPIO_CRL_CNF3_0 | GPIO_CRL_CNF4_0;
    GPIOB->CRL &= ~(GPIO_CRL_CNF1_1 | GPIO_CRL_CNF2_1 | GPIO_CRL_CNF3_1 | GPIO_CRL_CNF4_1);
}
void DisableInterrupts(void) {
    // V� hi?u h�a t?t c? ng?t
    __disable_irq();
}

void EnableInterrupts(void) {
    // K�ch ho?t t?t c? ng?t
    __enable_irq();
}

void Timer3A_Init(uint32_t period, uint32_t priority) {
    // K�ch ho?t clock cho Timer3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // T?t Timer3 tru?c khi c?u h�nh
    TIM3->CR1 &= ~TIM_CR1_CEN;

    // C?u h�nh chu k? v� chu k? t?i l?i
    TIM3->PSC = 0; // Chia t? l? cho b? chia tru?c
    TIM3->ARR = period - 1; // Chu k? t?i l?i

    // C?u h�nh uu ti�n ng?t
    NVIC_SetPriority(TIM3_IRQn, priority);

    // K�ch ho?t ng?t tr�n TIM3
    TIM3->DIER |= TIM_DIER_UIE;

    // X�a c? c?nh b�o tr�n
    TIM3->SR &= ~TIM_SR_UIF;

    // K�ch ho?t Timer3
    TIM3->CR1 |= TIM_CR1_CEN;
}
void Timer3A_Stop(void) {
    NVIC_DisableIRQ(TIM3_IRQn); // V� hi?u h�a ng?t t? Timer3
    TIM3->CR1 &= ~TIM_CR1_CEN; // T?t Timer3
}
void DelayMilliseconds(uint32_t milliseconds) {
    volatile uint32_t i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 6000; j++) { // Thay d?i gi� tr? n�y d? di?u ch?nh th?i gian ch?
            // Do-nothing loop
        }
    }
}
uint32_t Convert(uint32_t input) {
    return ((56 * (input)) + 27891) / 128; // C�c h?ng s? du?c s? d?ng t? du?ng cong ph� h?p v?i b?ng d? li?u
}

int main(void) {
    int delay;
    DisableInterrupts();
    //PLL_Init();
    
    USART_Init();   // Kh?i t?o UART
   

    Timer3A_Init(160000, 0); // Kh?i t?o Timer3
    //ADC_Init();
   // ST7735_InitR(INITR_REDTAB);
    PortB_Init();

    EnableInterrupts();

    while (1) { // Ch?y m?i 10ms
        // Vi?t ph?n n�y
        // G?i InChar c?a b?n (FIFO get) v� d?i cho d?n khi c� d? li?u m?i d?n.
        //ST7735_SetCursor(0, 0);
        while (1) {
            // �?i cho d?n khi th?y byte �<�
            // G?i InChar c?a b?n (FIFO get) th�m 5 l?n
            //ST7735_OutChar(Fifo_Get());
            //ST7735_OutChar(Fifo_Get());
            //ST7735_OutChar(Fifo_Get());
            //ST7735_OutChar(Fifo_Get());
            //ST7735_OutChar(Fifo_Get());
            //ST7735_OutString("     cm");
					USART2_OutChar((char)"a");
					//UART2_SendString("Hello World");
					DelayMilliseconds(600);
					
        }

        // Nam k� t? ti?p theo sau byte �<� n�n l� bi?u di?n ASCII c?a kho?ng c�ch
        // Xu?t s? c? d?nh (c�ng d?nh d?ng nhu Lab 8) v?i don v? tr�n m�n h�nh LCD.
    }
}