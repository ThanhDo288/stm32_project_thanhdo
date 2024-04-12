#include <stdint.h>
#include "stm32f10x.h"
#include "DAC.h"
#include "Sound.h"

unsigned long Index=0;
unsigned long int Index_2;
unsigned short Sound_On_Flag;
const uint8_t SineWave[32] = {0,1,2,5,9,14,20,26,32,38,44,50,54,59,61,63,63,63,61,59,54,50,44,38,32,26,20,14,9,5,2,1};
void Sound_Init(void){
	 
   // DAC_Init();

    SysTick->CTRL = 0;

    
    SysTick->LOAD = 35999;

   
    SysTick->VAL = 0;

   
    NVIC_SetPriority(SysTick_IRQn, 0);

  
    SysTick->CTRL = SysTick_CTRL_ENABLE | SysTick_CTRL_CLKSOURCE | SysTick_CTRL_TICKINT;

	}
void Sound_Start(uint32_t period){
	SysTick->CTRL = 0;
	SysTick->LOAD = period-1;
	SysTick->VAL = 0;
	NVIC_SetPriority(SysTick_IRQn, 0);
	 SysTick->CTRL =0x07;
	}
void SysTick_Handler(void){
//Index = (Index+1)&0x3F; //index increments from 0 to 31 and then starts back at 0 again
Sound_On_Flag=1;
if(Sound_On_Flag){
DAC_Out(SineWave[(Index++)&0x1F]);

	}
	else{
		DAC_Out(0);
	}
//GPIO_PORTB_DATA_R ^= 0x3F;
}