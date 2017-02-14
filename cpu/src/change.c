#include "./../include/cpu.h"

extern accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern sc_register;

int changeAccumulator(int pos)
{
  int plusFlag, num;
  refreshGui(pos);
  if (scanNum(&plusFlag, &num) != 0) {
    printf("Not a number!");
    return -1;
  }
  if ((num >= 0) && (num < 0x8000)) {
    accumulator = num;
  } else {
    printf("Accumutalor is 15 bit wide");
    return -1;
  }
  return 0;
}
/*------------------------------------------------------------------------------*/
int scanNum(int *plusFlag, int *n)
{
  char buffer[256];
  int pos = 0;
 
  fgets(buffer, 256, stdin);
  if (buffer[0] == '+') {
    pos = 1;
    *plusFlag = 1;
  } else {
    *plusFlag = 0;
  }
  if (sscanf(buffer + pos, "%x", n) != 1) {
    return -1;
  }
  return 0;
}
