#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;

int readMcell(int pos)
{
  int plusFlag, num;
  int command, operand, mem;

  refreshGui(instructionRegisterCount);
  write(1,"READ: ", 6);
  writeInt(1,pos,10,-1);
  if (scanNum(&plusFlag, &num) != 0) {
    write(2, "Not a number!", 13);
    return -1;
  }
  if ((num >= 0) && (num < 0x8000)) {
    if (plusFlag) {
      if (((num >> 7) & 1) == 1) {
         printf("Wrong instruction allign");
        return -1;
      }
      command = (num >> 8) & 0x7F;
      operand = num & 0x7F;
      mem = (command << 7) | operand;
    } else 
      mem = (1 << 14) | num;
    if ((pos >= 0) && (pos < sizeRAM))  
      sc_memorySet(pos, mem);
  } else {
    write(2, "Memory cell is 15 bit wide", 25);
    return -1;
  }
  return 0;
}
