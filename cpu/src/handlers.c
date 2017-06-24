/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int accumulator;
extern int instructionPointer;
extern int writeUse;

void timerHand(int sig)
{
  int reg;
  sc_regGet(FLAG_INTERRUPT, &reg);
  if (reg == 0) {
    CU();
    refreshGui(instructionPointer);
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
  instructionPointer = 0;
}
/*---------------------------------------------------------------------------*/
void ursignalHand2(int sig)
{
  setitimer(TIMER, NULL, NULL);
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
  setitimer(TIMER, NULL, NULL);
  mt_clrscr();
  rk_mytermrestore();
  signalsRestore();
  system("rm -f termsettings");
  exit(0);
}
