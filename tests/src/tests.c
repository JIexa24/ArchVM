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
    write(1, TEST_FAIL, strlen(TEST_FAIL));
    write(1, "Test sc_memoryInit(): FAIL", 26);
  } else {
    write(1, TEST_OK, strlen(TEST_OK));
    write(1, "\n", 1);
    write(1, "Test sc_memoryInit(): OK", 24);
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
int test_sc_memorySet()
{
  int ret = 0;
  int retf = sc_memorySet(1, 6);

  if (!retf) {
    if (!(localRAM[1] == 6)) {
      ret = 1;
    } else {
      ret = ret;
    }
  } else {
    ret = 1;
  }

  retf = sc_memorySet(100, 6);
  if (!retf) { 
    ret = 1;
  } else {
    ret = ret;
  }

  if (ret) {
    write(1, "\n", 1);
    write(1, TEST_FAIL, strlen(TEST_FAIL));
    write(1, "Test sc_memorySet(): FAIL", 26);
  } else {
    write(1, TEST_OK, strlen(TEST_OK));
    write(1, "\n", 1);
    write(1, "Test sc_memorySet(): OK", 24);
  }
  return ret;
}
