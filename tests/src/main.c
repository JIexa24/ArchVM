/*
  Created by JIexa24 (Alexey R.)
*/
#include "../include/tests.h"

int main(int argc, char** argv)
{
  int ret = 0;

  writeChar(1, "\n");
  mt_setfgcolor(clr_cyan);
  writeChar(1, "Running tests...\n");
  mt_setfgcolor(clr_default);

  ret = !(test_sc_memoryInit())    ? ret : 1;
  ret = !(test_sc_memorySet())     ? ret : 1;
  ret = !(test_sc_memoryGet())     ? ret : 1;
  ret = !(test_sc_regInit())       ? ret : 1;
  ret = !(test_sc_regSet())        ? ret : 1;
  ret = !(test_sc_regGet())        ? ret : 1;
  ret = !(test_sc_commandEncode()) ? ret : 1;
  ret = !(test_sc_commandDecode()) ? ret : 1;

  writeChar(1, "\n");

  ret = !(test_asmCommand()) ? ret : 1;

  writeChar(1, "\n");

  ret = !(test_keywordCode()) ? ret : 1;

  mt_setfgcolor(clr_default);
  writeChar(1, "\n");

  return ret;
}
