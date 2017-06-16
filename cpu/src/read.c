/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int instructionRegisterCount;

int readMcell(int pos)
{
  setIgnoreAlarm();
  setEchoRegime();
  int plusFlag = 0;
  int num      = 0;
  int ret      = 0;
  int command  = 0;
  int operand  = 0;
  int mem      = 0;

  refreshGui(instructionRegisterCount);
  mt_gotoXY(1, 23);
  writeChar(1,"READ: ");
  mt_gotoXY(1, 24);

  ret = changeCell(pos);

  restoreEchoRegime();
  restoreIgnoreAlarm();
  return ret;
}
