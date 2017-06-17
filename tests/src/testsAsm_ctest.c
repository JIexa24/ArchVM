/*
  Created by JIexa24 (Alexey R.)
*/
#include "../include/tests.h"

CTEST(asmCommand, test_asmCommand)
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

  ASSERT_EQUAL(0, ret);
}
