/*
  Created by JIexa24 (Alexey R.)
*/
#define CTEST_MAIN
#define CTEST_SEGFAULT
#define CTEST_COLOR_OK

#include "../include/tests.h"

int main(int argc, char** argv)
{
  int ret = ctest_main(argc, (const char**)argv);
  return ret;
}
