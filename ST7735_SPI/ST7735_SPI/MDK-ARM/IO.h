#ifndef IO_H
#define IO_H

#include <stdint.h>
// Initialize GPIO Port for a switch and an LED
void IO_Init(void);

// Toggle the output stage of the LED
void IO_HeartBeat(void);

// Wait for release and touch of the switch
void IO_Touch(void);

#endif