/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

int accumulator              = 0;
int instructionPointer       = 0;
int bigChars[34]             = {0};
int writeUse                 = 0;
int writeValue               = 0;
int SCANPRINTRADIX           = 16;
int readUse                  = 0;
int position                 = 0;
int cursorX                  = 0;
int cursorY                  = 0;
