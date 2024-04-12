
#include <stdint.h>
#include "PLL.h"
#include "stm32f10x.h"

void SysTick_Wait(uint32_t period) {
    SysTick->CTRL = 0;
    SysTick->LOAD = period - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE;
}

void SysTick_Waitms(uint32_t ms) {
    uint32_t period = 80000 * ms;
    SysTick_Wait(period);
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0) {}
}




#define periou 10000
#define start 2000
#define change 2000
void PortInit( void ){
	
	// Initialize GPIO ports 
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN; // PortA,PortB,PortC
	
	// set A0,A1 as switches
	GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0 | GPIO_CRL_MODE1 | GPIO_CRL_CNF1 ) ;
	GPIOA->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 ; // pull up mode
	
	// set B10 light output
	GPIOB->CRH &= ~(GPIO_CRH_MODE10|GPIO_CRH_CNF10 );
	GPIOB->CRH |= GPIO_CRH_MODE10_0;	
}
uint32_t dutycycle=start;
void IO_Touch(void) {
    // Wait for release (PA0 high)
    while (!(GPIOA->IDR & GPIO_IDR_IDR0)) {}
			SysTick_Waitms(start);
    // Wait for press (PA0 low)
    while (GPIOA->IDR & GPIO_IDR_IDR0) {}
}
void IO_HeartBeat(void) {
    // Toggle the output state of Pin 9 (LED)
    GPIOB->ODR ^= GPIO_ODR_ODR8;
}

int main(void){
	//SysTick_Init();
	PLL_Init();
	PortInit();
	uint32_t buttonPressed = 0;
	//SysTick_Config(SystemCoreClock / 1000);
while(1){
	if (GPIOA->IDR & GPIO_IDR_IDR0) {
            // Nút không du?c nh?n
            buttonPressed = 0;
        } else {
            // Nút du?c nh?n
            if (!buttonPressed) {
                // N?u nút v?a du?c nh?n, tang th?i gian sáng thêm 1 giây (1000ms)
                dutycycle += change;
                buttonPressed = 1;
            }
        }
	if(dutycycle<periou){
		 GPIOB->BSRR = GPIO_BSRR_BS10;
        SysTick_Waitms(dutycycle);  // B?t trong 1 giây

        GPIOB->BSRR = GPIO_BSRR_BR10;
        SysTick_Waitms(periou-dutycycle);  // T?t trong 2 giây
		}
	else dutycycle=start;
	}
}
