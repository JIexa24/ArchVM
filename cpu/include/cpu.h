/*
  Created by JIexa24 (Alexey R.)
*/
#ifndef CPU_H
#define CPU_H

#include "./../../simpleComputer/include/sc_register.h"
#include "./../../simpleComputer/include/sc_command.h"
#include "./../../simpleComputer/include/sc_memory.h"
#include "./../../bc/include/bc.h"
#include "./../../consoleSC/include/term.h"
#include "./../../readKey/include/readkey.h"
#include "./../../print/include/writeInt.h"
#include "./../../scan/include/readInt.h"
#include "./../../hardDrive/include/hardDrive.h"
#include "./../../asm/include/asm.h"

#include <signal.h>
#include <fcntl.h>

/* CPU */

#define BIGCHARSCOLORFG clr_cyan
#define BIGCHARSCOLORBG clr_default

#define TEXTCOLORFG clr_black
#define TEXTCOLORBG clr_green

#define INSTREGCOLORG clr_yellow

#define REGCOLOR clr_blue


void CU();
int ALU(int command, int operand);

void timerHand(int sig);
void ursignalHand(int sig);
void windHand(int sig);
void killHand(int sig);

void refreshGuiSt(int position);
void refreshGui(int position);
void printBoxes();
void printCounter();
void printAccum();
void printKeys(int x, int y);
void printLabels();
void printOperation(int position);
void printFlags(int x, int y);
int printMcell(int *bigchars, int pos);
void printLine(int ctr);
void printMemory(int x, int y, int position);

void setSignals();
int changeAccumulator(int pos);
int changeInstRegisterCount(int pos);
int changeCell(int pos);
int scanNum(int *plusFlag, int *n);

int memorySave(int position);
int memoryLoad(int position);

static void printWriteValue();

int commandHandler(int command, int operand);

int readMcell(int pos);

#endif
