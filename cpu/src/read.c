/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int instructionRegisterCount;

int readMcell(int pos)
{
  int plusFlag = 0;
  int num      = 0;
  int ret      = 0;
  int command  = 0;
  int operand  = 0;
  int mem      = 0;

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
