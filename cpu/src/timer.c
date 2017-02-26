#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;

void timerHand(int sig)
{
  refreshGui(instructionRegisterCount);
  CU();
  instructionRegisterCount++;
  if (!BITCHECK(sc_register, FLAG_INTERRUPT)) {
    alarm(1);
  }
}

void timerUrsignalHand(int sig)
{
  sc_regInit();
  sc_regSet(FLAG_INTERRUPT, 1);
  instructionRegisterCount = 0;
  accumulator = 0;
}
