#include "../include/tests.h"

int main ()
{
  int ret = 0;
  
  ret = !(test_sc_memoryInit()) ? ret : 1;

  write(1, "\n", 1);
  return ret;
}
