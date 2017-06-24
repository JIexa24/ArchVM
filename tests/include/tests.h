/*
  Created by JIexa24 (Alexey R.)
*/
#ifndef TEST_H
#define TEST_H

#include "../../thirdparty/tests.h"
#include "../../thirdparty/ctest.h"

int test_sc_memoryInit();
int test_sc_memorySet();
int test_sc_memoryGet();
int test_sc_regInit();
int test_sc_regSet();
int test_sc_regGet();
int test_sc_commandEncode();
int test_sc_commandDecode();
/*---------------------------------------------------------------------------*/
int test_asmCommand();
/*---------------------------------------------------------------------------*/
int test_keywordCode();

#endif
