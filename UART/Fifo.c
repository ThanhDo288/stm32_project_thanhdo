
#include <stdint.h>
#include "UART.h"



#define FIFO_SIZE 7
static uint8_t PutI;  // index to put new
static uint8_t GetI;  // index of oldest
static char Fifo[FIFO_SIZE];
// *********** FiFo_Init**********
// Initializes a software FIFO of a
// fixed size and sets up indexes for
// put and get operations

void Fifo_Init(){
  PutI = GetI = 0;  // empty
}
// *********** FiFo_Put**********
// Adds an element to the FIFO
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
uint32_t Fifo_Put(char data){
  //Complete this routine
   if(((PutI+1)%FIFO_SIZE) == GetI) return 0; // fail if full
  Fifo[PutI] = data;         // save in Fifo
  PutI = (PutI+1)%FIFO_SIZE; // next place to put
  return 1;

}

// *********** Fifo_Get**********
// Gets an element from the FIFO
// Input: none
// Output: If the FIFO is empty return 0
//         If the FIFO has data, remove it, and return it
uint32_t Fifo_Get(void){
  //Complete this routine
  if(GetI == PutI) return 0; // fail if empty
  char Get= GetI;      // retrieve data
  GetI = (GetI+1)%FIFO_SIZE; // next place to get
  return Fifo[Get];
}



