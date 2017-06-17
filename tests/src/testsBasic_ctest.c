/*
  Created by JIexa24 (Alexey R.)
*/
#include "../include/tests.h"

CTEST(keywordCode, test_keywordCode)
{
  int ret = 0;

  if (keywordCode("INPUT") == KEYW_INPUT) {
    ret = ret;
  } else {
    ret = 1;
  }

  if (keywordCode("OUTPUT") == KEYW_OUTPUT) {
    ret = ret;
  } else {
    ret = 1;
  }

  if (keywordCode("otherval") == KEYW_E) {
    ret = ret;
  } else {
    ret = 1;
  }
  if (keywordCode("GOTO") == KEYW_GOTO) {
    ret = ret;
  } else {
    ret = 1;
  }

  if (keywordCode("IF") == KEYW_IF) {
    ret = ret;
  } else {
    ret = 1;
  }

  if (keywordCode("LET") == KEYW_LET) {
    ret = ret;
  } else {
    ret = 1;
  }

  if (keywordCode("END") == KEYW_END) {
    ret = ret;
  } else {
    ret = 1;
  }

  ASSERT_EQUAL(0, ret);
}
