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
  CU();
  refreshGui(instructionRegisterCount);
  sc_regGet(FLAG_INTERRUPT, &reg);
  if (!reg) {
    /* raise для непрерывного выполнения. alarm - одна секунда */  
    // raise(SIGALRM);
    alarm(1);
  }
}
/*---------------------------------------------------------------------------*/
void ursignalHand(int sig)
{
  sc_memoryInit();
  sc_regInit();
  sc_regSet(FLAG_INTERRUPT, 1);
  accumulator = 0;
  writeUse = 0;
  instructionRegisterCount = 0; 
}
/*---------------------------------------------------------------------------*/
void ursignalHand2(int sig)
{
  sc_regSet(FLAG_INTERRUPT, 1);
}
/*---------------------------------------------------------------------------*/
void windHand(int sig)
{
  refreshGuiSt(0);
}
/*---------------------------------------------------------------------------*/
void killHand(int sig)
{ 
  mt_clrscr();
  rk_mytermrestore();
  system("rm -f termsettings");
  exit(0);
}
