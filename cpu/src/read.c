/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;

int readMcell(int pos)
{
  int plusFlag, num;
  int command, operand, mem;

  struct termios orig_options;
  
  if (tcgetattr(STDIN_FILENO, &orig_options) != 0) {
    return -1;
  }
  rk_mytermregime(0, 0, 1, 1, 1);
 
  refreshGui(instructionRegisterCount);
  writeChar(1,"READ: ");
//  writeInt(1,pos,10,-1);
  if (scanNum(&plusFlag, &num) != 0) {
    if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0) {
      return -1;
    }
    writeChar(2, "Not a number!");
    return -1;
  }
  if ((num >= 0) && (num < 0x8000)) {
    if (plusFlag) {
      if (((num >> 7) & 1) == 1) {
        if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0) {
          return -1;
        } 
        writeChar(2, "Wrong instruction allign");
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
    if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0) {
      return -1;
    }
    writeChar(2, "Memory cell is 15 bit wide");
    return -1;
  }

  if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0) {
    return -1;
  }

  return 0;
}
