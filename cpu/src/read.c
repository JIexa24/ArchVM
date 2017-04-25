/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int instructionRegisterCount;

int readMcell(int pos)
{
  int plusFlag, num, ret = 0;
  int command, operand, mem;

  struct termios orig_options;
  
  if (tcgetattr(STDIN_FILENO, &orig_options) != 0) {
    return -1;
  }
  rk_mytermregime(0, 0, 1, 1, 1);
 
  refreshGui(instructionRegisterCount);
  mt_gotoXY(1, 23);
  writeChar(1,"READ: ");
  mt_gotoXY(1, 24);

  ret = changeCell(pos);

  if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0) {
    return -1;
  }

  return ret;
}
