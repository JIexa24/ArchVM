/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/asm.h"

int asmCommand(char *str)
{
  int ret;
  if (strcmp(str, "READ") == 0) {
    ret = 0x10;
  } else if (strcmp(str, "WRITE") == 0) {
    ret = 0x11;
  } else if (strcmp(str, "LOAD") == 0) {
    ret = 0x20;
  } else if (strcmp(str, "STORE") == 0) {
    ret = 0x21;
  } else if (strcmp(str, "ADD") == 0) {
    ret = 0x30;
  } else if (strcmp(str, "SUB") == 0) {
    ret = 0x31;
  } else if (strcmp(str, "DIVIDE") == 0) {
    ret = 0x32;
  } else if (strcmp(str, "MUL") == 0) {
    ret = 0x33;
  } else if (strcmp(str, "JUMP") == 0) {
    ret = 0x40;
  } else if (strcmp(str, "JNEG") == 0) {
    ret = 0x41;
  } else if (strcmp(str, "JZ") == 0) {
    ret = 0x42;
  } else if (strcmp(str, "HALT") == 0) {
    ret = 0x43;
  } else if (strcmp(str, "JNP") == 0) {
    ret = 0x59;
  } else if (strcmp(str, "ADD") == 0) {
    ret = 0x52;
  } else {
    ret = -1;
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
