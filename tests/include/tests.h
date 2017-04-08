#ifndef TEST_H
#define TEST_H

#include "../../thirdparty/tests.h"

#include "../../simpleComputer/include/sc_memory.h"
#include "../../simpleComputer/include/sc_register.h"
#include "../../simpleComputer/include/sc_command.h"

int test_sc_memoryInit();
int test_sc_memorySet();
int test_sc_memoryGet();
int test_sc_regInit();
int test_sc_commandEncode();
int test_sc_commandDecode();
#endif
