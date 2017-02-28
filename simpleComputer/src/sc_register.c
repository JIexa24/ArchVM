/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/sc_register.h"

/*
  ERR_WRONG_ADDR -1
  ERR_OPEN_FILE -2
  ERR_FILE -3
  ERR_UNCORRECT_COMMAND -4
  ERR_ATTRIBUTE_BIT -5
  ERR_WRONG_FLAG -6

  int localRAM[sizRAM];
  short int sc_register;
  const int correctCommands[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 
                               0x40, 0x41, 0x42, 0x43, 0x52, 0x59};
  const int countCmd = 13;
*/

extern int localRAM[];
extern short int sc_register;

extern int* correctCommands;


int sc_regInit(void)
{
  sc_register = 0;
  return 0;
}
/*---------------------------------------------------------------------------*/
int sc_regSet(int scRegister, int value)
{
  if ((scRegister >= 0) && (scRegister <=5) && (value >= 0) && (value < 2)) {
    if (value == 1) {
      BITSET(sc_register, scRegister);
    } else if (value == 0) {
      BITCLEAR(sc_register, scRegister);
    } else {
	  return 0;
    }		
  }	else {
    return ERR_WRONG_FLAG;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
int sc_regGet(int scRegister, int* value)
{
  if ((scRegister >= 0) && (scRegister <=6)) {
    *value = BITCHECK(sc_register, scRegister);
    return *value;
  } else { 
    return ERR_WRONG_FLAG;
  }
  return 0;
}
