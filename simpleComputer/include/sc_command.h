/*
  Operation with commandcode
*/

#ifndef SC_COMMAND_H
#define SC_COMMAND_H

#include "./sc.h"

int sc_commandEncode(int* value, int command, int operand);

int sc_commandDecode(int value, int* command, int* operand);

#endif
