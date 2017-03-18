/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;
extern int writeUse; 

void timerHand(int sig)
{
  int reg;
  if (instructionRegisterCount < sizeRAM) {
    CU();
    refreshGui(instructionRegisterCount);

    sc_regGet(FLAG_INTERRUPT, &reg);
    if (!reg) {
      /* raise для непрерывного выполнения. alarm - одна секунда */  
      // raise(SIGALRM);
      alarm(1);
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
