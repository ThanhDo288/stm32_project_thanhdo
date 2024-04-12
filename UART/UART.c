#include <stdint.h>
#include<stm32f10x.h>
#include "Fifo.h"
#include "UART.h"
#include "PLL.h"
int RxCounter=0;
void USART_Init(void){
	PLL_Init();

RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
GPIOA->CRL = 0;
GPIOA->CRL |= (3<<8);   // output mode 50 MHz for PA2
GPIOA->CRL |= (2<<10);  // Alternate Func Push Pull For PA2
	
GPIOA->CRL &= ~(3<<12);   // Intput Mode For PA3
GPIOA->CRL |= (2<<14);  // Input Pull Up/ Down For PA3	
	
GPIOA->ODR |= 1<<3;  // Pull Up for PA3
	
USART2->CR1 = 0x00;   // Clear ALL
USART2->CR1 |= (1<<13);   // UE = 1... Enable USART
USART2->BRR = SystemCoreClock /(8*9600);// (7<<0) | (24<<4);   // Baud rate of 115200, PCLK1 at 45MHz
	
USART2->CR1 |= (1<<2); // RE=1 Enable the Receiver
USART2->CR1 |= (1<<3);  // TE=1.. Enable Transmitter 
	}
char USART2_InChar(void){
	while((USART2->SR & USART_SR_RXNE) == 0); // Wait until RXNE flag is set  // wait until RXFE is 0
  return (char)(USART2->DR & 0xFF);
}
void UART2_SendString( char* str) {
    while (*str != '\0') {
        while (!(USART2->SR & USART_SR_TXE)); // Ð?i tr?ng d? g?i
        USART2->DR = (uint16_t)(*str++); // G?i t?ng ký t? trong chu?i
    }
}  
void USART2_OutChar(char data){
	while((USART2->SR & USART_SR_TXE) == 0); // Wait until TXE flag is set // wait until TXFF is 0
  USART2->DR = data;
}
void USART2_IRQHandler(void) {
    char letter;
  
    // Toggle heartbeat
    //GPIOF->ODR ^= GPIO_ODR_OD8;

    // Check for received data
    if ((USART2->SR & USART_SR_RXNE) != 0) { // Check if RXNE bit is set
        // Read the received byte
        letter = USART2->DR & 0xFF;
        // Put the byte into your software FIFO
        Fifo_Put(letter);
    }

    // Increment RxCounter
    RxCounter++;

    // Clear the interrupt flag
    USART2->SR &= ~USART_SR_RXNE;

    // Toggle heartbeat
    //GPIOF->ODR ^= GPIO_ODR_OD8;
}