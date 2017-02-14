#include "./../include/cpu.h"

extern accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;

void timerHand(int sig)
{
  refreshGui(instructionRegister);
  CU();
  instructionRegisterCount++;
  if (!BIT_CHECK(sc_register, FLAG_INTERRUPT)) {
    alarm(1);
  }
}
