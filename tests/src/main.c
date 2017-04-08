#include "../include/tests.h"

int main ()
{
  int ret = 0;
  
  ret = !(test_sc_memoryInit()) ? ret : 1;
  ret = !(test_sc_memorySet()) ? ret : 1;
  ret = !(test_sc_memoryGet()) ? ret : 1;
  ret = !(test_sc_regInit()) ? ret : 1;
  ret = !(test_sc_commandEncode()) ? ret : 1;
  ret = !(test_sc_commandDecode()) ? ret : 1;

  write(1, TEST_DEF, strlen(TEST_DEF));
  write(1, "\n", 1);
  write(1, "\n", 1);
  return ret;
}
