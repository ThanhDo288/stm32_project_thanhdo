
#ifndef IO_H
#define IO_H
#include <stdint.h>

void IO_Init(void);

//------------IO_HeartBeat------------
// Toggle the output state of the  LED.
// Input: none
// Output: none
void IO_HeartBeat(void);


//------------IO_Touch------------
// wait for release and touch of the switch
// Delay to debounce the switch
// Input: none
// Output: none
void IO_Touch(void);
void Wait10ms(uint32_t count);
#endif
