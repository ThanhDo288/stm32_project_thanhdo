#include "OutData.h"
#include "st7735.h"
#include "fonts.h"
#include "stdlib.h"

char Message[12];
uint32_t StTextColor = ST7735_GREEN;

void OutDec(uint32_t n, uint32_t x, uint32_t y){
	Dec2String(n, Message);
	ST7735_WriteString(x, y, Message, Font_7x10, StTextColor, ST7735_BLACK);
}

void OutFix(uint32_t n, uint32_t x, uint32_t y){
	Fix2String(n, Message);
	ST7735_WriteString(x, y, Message, Font_7x10, StTextColor, ST7735_BLACK);
}