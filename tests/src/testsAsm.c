/*
  Created by JIexa24 (Alexey R.)
*/
#include "../include/tests.h"

int test_asmCommand()
{
  int ret = 0;

  if (asmCommand("READ") == 0x10) {
    ret = ret;
  } else {
    ret = 1;
  }

  if (asmCommand("DIVIDE") == 0x32) {
    ret = ret;
  } else {
    ret = 1;
  }

  if (asmCommand("test") == -1) {
    ret = ret;
  } else {
    ret = 1;
  }
  
  if (asmCommand("MOVCR") == 0x74) {
    ret = ret;
  } else {
    ret = 1;
  }

  if (ret) {
    mt_setfgcolor(TEST_FAIL);
    writeChar(1, "\n");
    writeChar(1, "Test asmCommand(): FAIL");
  } else {
    mt_setfgcolor(TEST_OK);
    writeChar(1, "\n");
    writeChar(1, "Test asmCommand(): OK");
  }
  mt_setfgcolor(TEST_DEF);
  return ret;
}
