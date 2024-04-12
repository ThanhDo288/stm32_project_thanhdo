#include "StringConversion.h"

void Dec2String(uint32_t num, char* str) {
    uint32_t count = 0;
    uint32_t tmp = num;
    do {
        tmp /= 10;
        count++;
    } while (tmp);
  
    str[count] = '\0';
    while (count > 0) {
        count--;
        str[count] = num % 10 + '0';
        num /= 10;
    }
}
void Fix2String(uint32_t num, char* str) {
	uint32_t count = 0;
	uint32_t tmp = num;
	uint32_t resolution = 1000;
	uint32_t i;
	if (num >= 0 && num < 9999) {
		while (resolution) {
			i = num / resolution;
			if (count == 1) {
				*(str + count) = '.';
				count++;
			}
			*(str + count) = i + '0';
			num %= resolution;
			resolution /= 10;
			count++;
		}
		*(str + count) = ' ';
		*(str + count) = '\0';
	}
	else {
		while (count != 5) {
			*(str + count) = '*';
			if (count == 1) {
				*(str + count) = '.';
			}
			count++;
		}
		*(str + count) = '\0';
	}
}
