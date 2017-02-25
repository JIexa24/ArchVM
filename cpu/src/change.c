#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;
/*
void setSignals()
{
  signal(SIGALRM, timerHand);
  signal(SIGUSR1, timerUrsignalHand);
}
/*---------------------------------------------------------------------------*/
int changeCell(int pos)
{
  int plusFlag, num;
  int command, operand, mem;

  refreshGui(pos);
  if (scanNum(&plusFlag, &num) != 0) {
    write(2, "Not a number!", 13);
    return -1;
  }
  if ((num >= 0) && (num < 0x8000)) {
      command = (num >> 8) & 0x7F;
      operand = num & 0x7F;
      mem = (command << 7) | operand;
      //sc_commandEncode(command, operand, &mem);
  } else 
    mem = (1 << 14) | num;

  if ((pos >= 0) && (pos < sizeRAM)) {
      sc_memorySet(pos, mem);
  } else {
    write(2, "Memory cell is 15 bit wide", 25);
    return -1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
int changeAccumulator(int pos)
{
  int plusFlag, num;
  refreshGui(pos);
  if (scanNum(&plusFlag, &num) != 0) {
    write(2, "Not a number!", 13);
    return -1;
  }
  if ((num >= 0) && (num < 0x8000)) {
    accumulator = num;
  } else {
    write(2, "Accumutalor is 15 bit wide", 26);
    return -1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
int changeInstRegisterCount(int pos)
{
  int plusFlag, num;

  refreshGui(pos);
  if (scanNum(&plusFlag, &num) != 0) {
    write(2, "Not a number!", 13);
    return -1;
  }
  if ((num >= 0) && (num < 0x100)) {
    instructionRegisterCount = num;
  } else {
    write(2, "Accumutalor range: from 0 to 99 (0x63)", 38);
    return -1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
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
