#include <stdint.h>
#include "stm32f10x.h"
#include "UART.h"
#include "PLL.h"
void PortB_Init(void) {
    // Kích ho?t clock cho c?ng GPIO Port B
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // C?u hình các chân GPIO PB1, PB2 và PB3 nhu d?u ra (output)
    GPIOB->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1 | GPIO_CRL_CNF2 | GPIO_CRL_MODE2 | GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
    GPIOB->CRL |= GPIO_CRL_MODE1_0 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE3_0;

    // C?u hình Pull-up cho chân GPIO PB4
    GPIOB->ODR |= GPIO_ODR_ODR4;

    // Kích ho?t ch?c nang digital cho các chân GPIO PB1, PB2, PB3 và PB4
    GPIOB->CRL |= GPIO_CRL_CNF1_0 | GPIO_CRL_CNF2_0 | GPIO_CRL_CNF3_0 | GPIO_CRL_CNF4_0;
    GPIOB->CRL &= ~(GPIO_CRL_CNF1_1 | GPIO_CRL_CNF2_1 | GPIO_CRL_CNF3_1 | GPIO_CRL_CNF4_1);
}
void DisableInterrupts(void) {
    // Vô hi?u hóa t?t c? ng?t
    __disable_irq();
}

void EnableInterrupts(void) {
    // Kích ho?t t?t c? ng?t
    __enable_irq();
}

void Timer3A_Init(uint32_t period, uint32_t priority) {
    // Kích ho?t clock cho Timer3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // T?t Timer3 tru?c khi c?u hình
    TIM3->CR1 &= ~TIM_CR1_CEN;

    // C?u hình chu k? và chu k? t?i l?i
    TIM3->PSC = 0; // Chia t? l? cho b? chia tru?c
    TIM3->ARR = period - 1; // Chu k? t?i l?i

    // C?u hình uu tiên ng?t
    NVIC_SetPriority(TIM3_IRQn, priority);

    // Kích ho?t ng?t trên TIM3
    TIM3->DIER |= TIM_DIER_UIE;

    // Xóa c? c?nh báo tràn
    TIM3->SR &= ~TIM_SR_UIF;

    // Kích ho?t Timer3
    TIM3->CR1 |= TIM_CR1_CEN;
}
void Timer3A_Stop(void) {
    NVIC_DisableIRQ(TIM3_IRQn); // Vô hi?u hóa ng?t t? Timer3
    TIM3->CR1 &= ~TIM_CR1_CEN; // T?t Timer3
}
void DelayMilliseconds(uint32_t milliseconds) {
    volatile uint32_t i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 6000; j++) { // Thay d?i giá tr? này d? di?u ch?nh th?i gian ch?
            // Do-nothing loop
        }
    }
}
uint32_t Convert(uint32_t input) {
    return ((56 * (input)) + 27891) / 128; // Các h?ng s? du?c s? d?ng t? du?ng cong phù h?p v?i b?ng d? li?u
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
        // Vi?t ph?n này
        // G?i InChar c?a b?n (FIFO get) và d?i cho d?n khi có d? li?u m?i d?n.
        //ST7735_SetCursor(0, 0);
        while (1) {
            // Ð?i cho d?n khi th?y byte ‘<’
            // G?i InChar c?a b?n (FIFO get) thêm 5 l?n
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

        // Nam ký t? ti?p theo sau byte ‘<’ nên là bi?u di?n ASCII c?a kho?ng cách
        // Xu?t s? c? d?nh (cùng d?nh d?ng nhu Lab 8) v?i don v? trên màn hình LCD.
    }
}