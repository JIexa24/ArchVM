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

#endif
