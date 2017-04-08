#include "../include/tests.h" 

extern int localRAM[];

int test_sc_memoryInit()
{
  int i;
  int ret = 0;
  sc_memoryInit();

  for (i = 0; i < sizeRAM; i++) {
    if (localRAM[i] != 0) {
      ret = 1;
    }
  }

  if (ret) {
    write(1, "\n", 1);
    write(1, "Test sc_memoryInit(): FAIL", 26);
  } else {
    write(1, "\n", 1);
    write(1, "Test sc_memoryInit(): OK", 24);
  }
  return ret;
}
