
		
#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "images.h".h"
#include "stm32f10x.h"
#include "IO.h"
#include "StringConversion.h"
#include "images.h"
// Modify these two with your EIDs
char EID1[]="abc1234";  // student's EID
char EID2[]="abc1235";  // student's EID
#define SIZE 16
uint32_t const TestData[SIZE] ={
  0,7,99,100,654,999,1000,5009,9999,10000,20806,65535,
  103456,12000678,123400009,0xFFFFFFFF
};


int main(void){  
  uint32_t i;
  PLL_Init(Bus80MHz);    
 // TExaS_Init(GRADER); // set system clock to 80 MHz
  // 1) implement SPIOutCommand and SPIOutData
  ST7735_InitR(INITR_REDTAB);
  ST7735_OutString("Lab 7 Spring 2023\n\xADHola!\nBienvenida al EE319K");
  // 2) remove lines the next two lines if the ST7735_OutString outputs correctly
//  while(1){
//  }
  IO_Init();
  IO_Touch();

  ST7735_FillScreen(0xFFFF);   // set screen to white
  ST7735_DrawBitmap(44, 159, Logo, 40, 160);
  IO_Touch();
  ST7735_FillScreen(0);       // set screen to black
  for(i=0;i<SIZE;i++){
    IO_HeartBeat();
    ST7735_SetCursor(0,i);
    ST7735_OutUDec(TestData[i]);
    ST7735_SetCursor(11,i);
    ST7735_OutFix(TestData[i]);
    IO_Touch(); // remove this line to see all test cases
  }
  while(1){
  }
}

