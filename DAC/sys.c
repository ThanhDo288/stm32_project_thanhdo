#include<stm32f10x.h>
#include"DAC.h"
#include"Sound.h"
#define Freq_key0 4828
#define Freq_key1 4555
#define Freq_key2 4300
#define Freq_key3 4058
void change_period(uint32_t period){
			Sound_Start(period);
}
	uint8_t Key_1=0;
	uint8_t Key_2;
void sys_init(){
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
	TIM2->CR1=0;
	TIM2->PSC=1;
	TIM2->ARR=0xFFFF;
	TIM2->DIER|=TIM_DIER_UIE;
	TIM2->CR1|=TIM_CR1_CEN;
}
void GPIO_Test(){
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
	GPIOA->CRH&=~(GPIO_CRH_MODE11|GPIO_CRH_CNF11);
	GPIOA->CRH|=GPIO_CRH_MODE11;
}
//void TIM2_IRQHandler(void){
// //int a=0;
//	if(TIM2->SR&TIM_SR_UIF){
//		GPIOA->ODR^=GPIO_ODR_ODR11;
//		TIM2->SR&=~TIM_SR_UIF;
//	}
//}
void Delay_ms(uint32_t delay){
	while(delay--){
		TIM2->CNT=0;
		while(TIM2->CNT<1000);
	}
}
int main(void){
	//ADC1//keyinit
	sys_init();
	GPIO_Test();
	Sound_Init();
	NVIC_SetPriority(TIM2_IRQn,0);
	NVIC_EnableIRQ(TIM2_IRQn);
	change_period(Freq_key0);
	while(1){
//		GPIOA->ODR^=GPIO_ODR_ODR11;
//	Delay_ms(10000);
//	GPIOA->ODR^=GPIO_ODR_ODR11;
//	Delay_ms(10000);
//		Key_2=Key_1;
//		Key_1=Key_In();
//		if(Key_1!=Key_2){
//			if(Key_1==1)change_period(Freq_key0);
//			if(Key_1==2) change_period(Freq_key1);
//			if(Key_1==4) change_period(Freq_key2);
//			if(Key_1==8) change_period(Freq_key3);
	}
}