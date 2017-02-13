#ifndef CPU_H
#define CPU_H

#include "./../../simpleComputer/include/sc.h"
#include "./../../simpleComputer/include/sc_register.h"
#include "./../../simpleComputer/include/sc_command.h"
#include "./../../simpleComputer/include/sc_memory.h"
#include "./../../bc/include/bc.h"
#include "./../../consoleSC/include/term.h"
#include "./../../readKey/include/readkey.h"

/* CPU */

void CU();
int ALU(int command, int operand);

int timerHand(int sig);

void refreshGui(int position);
void printBoxes();
void printCounter();
void printKeys(int x, int y);
void printLabels();
void printOperation(int position);
void printFlags(int x, int y);
int printMcell(int *bigchars, int pos)

int changeAccumulator(int pos);
int scanNum(int *plusFlag, int *n);

#endif
