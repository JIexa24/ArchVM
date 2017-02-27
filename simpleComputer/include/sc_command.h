/*
  Created by JIexa24 (Alexey R.)
*/
/*
  Operation with commandcode
*/

#ifndef SC_COMMAND_H
#define SC_COMMAND_H

#include "./sc.h"

int sc_commandEncode(int command, int operand, int* value);

int sc_commandDecode(int value, int* command, int* operand);

#endif
