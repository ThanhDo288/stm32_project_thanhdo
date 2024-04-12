#include <stdint.h>
#include "stm32f10x.h"
#include "DAC.h"
#include "Sound.h"
#include "Key.h"
void DisableInterrupts(void) {
    __disable_irq();
}

void EnableInterrupts(void) {
    __enable_irq();
}
#define RCC_APB1ENR_DACEN ((uint32_t)0x20000000)




uint8_t Testdata;
uint8_t Key_1=0;
uint8_t Key_2;

//const uint32_t Inputs[16]={0,1,7,8,15,16,17,18,31,32,33,47,48,49,62,63};


void change_period(uint32_t period){
			Sound_Start(period);
}
#define B  5062   // 493.9 Hz
#define A  5682   // 440.0 Hz
#define Gb  6757 // 370.0 Hz
#define D  11364 // 220Hz
void static DelayMs(uint32_t n){
  volatile uint32_t time;
  while(n){
    time = 6665;  // 1msec, tuned at 80 MHz
    while(time){
      time--;
    }
    n--;
  }
}
int main(void){       
  DisableInterrupts();
 // TExaS_Init(SIMULATIONGRADER);    // bus clock at 80 MHz
//    SCOPE,
//    LOGICANALYZERA,
//    LOGICANALYZERB,
//    LOGICANALYZERC,
//    LOGICANALYZERE,
//    REALBOARDGRADER,
//    SIMULATIONGRADER,
//    NONE
	DAC_Init();
  Key_Init();
	Sound_Start(10000);
 Sound_Init();
	
	//Sound_Start(50000);
 // Song_Init(); // extra credit 1)
 // Wave_Init(); // extra credit 2)
	Testdata = 0;
  EnableInterrupts();
	unsigned long input,previous;	
  while(1){   
DelayMs(1000);		
    input=Key_In();
		if(input&&(previous!=input)){ // just pressed     
			 switch(input){
				case 0x00:
					 change_period(D);      // Play note A wave
					 break; 
				case 0x02:   
					 change_period(Gb);      // Play note G wave
					 break; 
			
				case 0x04:  
					change_period(A);      // Play note F wave
					break;
				case 0x08:
					change_period(B);      // Play note C wave
					break; 
				default:
					break;
			} 
    }
    //if((input==0) && previous){ // just released    
		//	Sound_Off();    // stop sound }
    previous = input; 
       
  }
}



