/*
  Created by JIexa24 (Alexey R.)
*/
#include "../include/tests.h"

int main ()
{
  int ret = 0;
  
  ret = !(test_sc_memoryInit()) ? ret : 1;
  ret = !(test_sc_memorySet()) ? ret : 1;
  ret = !(test_sc_memoryGet()) ? ret : 1;
  ret = !(test_sc_regInit()) ? ret : 1;
  ret = !(test_sc_regSet()) ? ret : 1;
  ret = !(test_sc_regGet()) ? ret : 1;
  ret = !(test_sc_commandEncode()) ? ret : 1;
  ret = !(test_sc_commandDecode()) ? ret : 1;

  writeChar(1, TEST_DEF);
  writeChar(1, "\n");
  writeChar(1, "\n");
  return ret;
}
