
#ifndef UART_H
#define UART_H
#include <stdint.h>

void USART_Init(void);
char USART2_InChar(void);
void  UART2_SendString(char*);
void USART2_OutChar(char data);

#endif
