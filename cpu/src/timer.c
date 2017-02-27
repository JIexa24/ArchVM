#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;
extern int writeUse; 
extern int flagHalt;

void timerHand(int sig)
{
  if (instructionRegisterCount < sizeRAM) {
    refreshGui(instructionRegisterCount);
    CU();
    if (!flagHalt) {
      instructionRegisterCount++;
    }
    if (!BITCHECK(sc_register, FLAG_INTERRUPT)) {
      /* raise для непрерывного выполнения. alarm - одна секунда */  
      raise(SIGALRM);
      //alarm(1);
    }
  } else {
    sc_regSet(FLAG_INTERRUPT, 1);
    sc_regSet(FLAG_OUTMEM, 1); 
    refreshGui(instructionRegisterCount);
    instructionRegisterCount = 0; 
  }
}
/*---------------------------------------------------------------------------*/
void timerUrsignalHand(int sig)
{
  sc_regInit();
  sc_regSet(FLAG_INTERRUPT, 1);
  instructionRegisterCount = 0; 
  accumulator = 0;
  writeUse = 0;
}
