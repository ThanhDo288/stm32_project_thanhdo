#include<stm32f10x.h>
#include"DAC.h"
const uint8_t sinwave[32] ={0,1,2,5,9,14,20,26,32,38,44,50,54,59,61,63,63,63,61,59,54,50,44,38,32,26,20,14,9,5,2,1};
	const uint8_t sinwave1[32] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	uint16_t index=0;
void Sound_Init(){
	DAC_Init();
	TIM2->CR1=0;
	TIM2->ARR=9000-1;
	TIM2->DIER|=TIM_DIER_UIE;
	TIM2->CR1|=TIM_CR1_CEN;
}
void Sound_Start(int period){
	DAC_Init();
	TIM2->CR1=0;
	TIM2->ARR=period-1;
	TIM2->DIER|=TIM_DIER_UIE;
	TIM2->CR1|=TIM_CR1_CEN;
}
void Sound_Voice(const uint8_t *voice){
	DAC_Init();
  // optional
	DAC_Out(voice[index]);
	index=index+1;
	if(index==31) index=0;
}
void TIM2_IRQHandler(void){
 //int a=0;
	if(TIM2->SR&TIM_SR_UIF){
Sound_Voice(sinwave);
		TIM2->SR&=~TIM_SR_UIF;
	Sound_Voice(sinwave);
	}