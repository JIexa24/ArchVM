/*
  Created by JIexa24 (Alexey R.)
*/
#include "../include/tests.h" 

extern int localRAM[];
extern short int sc_register;

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
    writeChar(1, "\n");
    writeChar(1, TEST_FAIL"Test sc_memoryInit(): FAIL");
  } else {
    writeChar(1, "\n");
    writeChar(1, TEST_OK"Test sc_memoryInit(): OK");
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
  retf = sc_memorySet(-15, 6);
  if (!retf) { 
    ret = 1;
  } else {
    ret = ret;
  }

  if (ret) {
    writeChar(1, "\n");
    writeChar(1, TEST_FAIL"Test sc_memorySet(): FAIL");
  } else {
    writeChar(1, "\n");
    writeChar(1, TEST_OK"Test sc_memorySet(): OK");
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
int test_sc_memoryGet()
{
  int ret = 0;
  int value;
  int retf;
  const int val = 15;
  const int ind = 10;

  localRAM[ind] = val;

  retf = sc_memoryGet(ind, &value);
  if (!retf) {
    if (!(localRAM[ind] == val)) {
      ret = 1;
    } else {
      ret = ret;
    }
  } else {
    ret = 1;
  }

  retf = sc_memoryGet(-5, &value);
  if (!retf) {  
    ret = 1;
  } else {
    ret = ret;
  }

  retf = sc_memoryGet(sizeRAM, &value);
  if (!retf) {  
    ret = 1;
  } else {
    ret = ret;
  }

  if (ret) {
    writeChar(1, "\n");
    writeChar(1, TEST_FAIL"Test sc_memoryGet(): FAIL");
  } else {
    writeChar(1, "\n");
    writeChar(1, TEST_OK"Test sc_memoryGet(): OK");
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
int test_sc_regInit()
{
  int i;
  int ret = 0;
  sc_regInit();

  if (!sc_register) {
    ret = ret;
  } else {
    ret = 1;
  }

  if (ret) {
    writeChar(1, "\n");
    writeChar(1, TEST_FAIL"Test sc_regInit(): FAIL");
  } else {
    writeChar(1, "\n");
    writeChar(1, TEST_OK"Test sc_regInit(): OK");
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
int test_sc_regSet()
{
  int i;
  int ret = 0;
  int retf;

  sc_register = 0;
  retf = sc_regSet(FLAG_OUTMEM, 1);

  if (!retf) {
    if (!(sc_register == 4)) {
      ret = 1;
    } else {
      ret = ret;
    }
  } else {
    ret = 1;
  }

  retf = sc_regSet(FLAG_OUTMEM, 0);
  if (!retf) {
    if (!sc_register) {
      ret = ret;
    } else {
      ret = 1;
    }
  } else {
    ret = 1;
  }

  retf = sc_regSet(FLAG_OUTMEM, 4);
  if (!retf) {
    ret = 1;
  } else {
    ret = ret;
  }

  retf = sc_regSet(10, 0);
  if (retf == 0) {
    ret = 1;
  } else {
    ret = ret;
  }

  if (ret) {
    writeChar(1, "\n");
    writeChar(1, TEST_FAIL"Test sc_regSet(): FAIL");
  } else {
    writeChar(1, "\n");
    writeChar(1, TEST_OK"Test sc_regSet(): OK");
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
int test_sc_regGet()
{
  int i;
  int ret = 0;
  int retf;
  int flag;

  sc_register = 0x4;

  retf = sc_regGet(FLAG_OUTMEM, &flag);
  if (!retf) {
    if (flag) {
      ret = ret;
    } else {
      ret = 1;
    }
  } else {
    ret = 1;
  }

  sc_register = 0x1;
  retf = sc_regGet(FLAG_OUTMEM, &flag);
  if (!retf) {
    if (flag) {
      ret = 1;
    } else {
      ret = ret;
    }
  } else {
    ret = 1;
  }

  retf = sc_regGet(100, &flag);
  if (!retf) {
    ret = 1;
  } else {
    ret = ret;
  }

  if (ret) {
    writeChar(1, "\n");
    writeChar(1, TEST_FAIL"Test sc_regGet(): FAIL");
  } else {
    writeChar(1, "\n");
    writeChar(1, TEST_OK"Test sc_regGet(): OK");
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
int test_sc_commandEncode()
{
  int ret = 0;
  int value;
  int retf;

  retf = sc_commandEncode(0x10, 0x10, &value);
  if (!retf) {
    if (!(value == 0x0810)) {
      ret = 1;
    } else {
      ret = ret;
    }
  } else {
    ret = 1;
  }

  if (ret) {
    writeChar(1, "\n");
    writeChar(1, TEST_FAIL"Test sc_commandEncode(): FAIL");
  } else {
    writeChar(1, "\n");
    writeChar(1, TEST_OK"Test sc_commandEncode(): OK");
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
int test_sc_commandDecode()
{
  int ret = 0;
  int com, op;
  int retf;

  retf = sc_commandDecode(0x0810, &com, &op);
  if (!retf) {
    if (!(com == 0x10 && op == 0x10)) {
      ret = 1;
    } else {
      ret = ret;
    }
  } else {
    ret = 1;
  }

  if (ret) {
    writeChar(1, "\n");
    writeChar(1, TEST_FAIL"Test sc_commandDecode(): FAIL");
  } else {
    writeChar(1, "\n");
    writeChar(1, TEST_OK"Test sc_commandDecode(): OK");
  }
  return ret;
}
