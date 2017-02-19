#include "./../include/writeInt.h"

#define SIZE_BUFFER 100

int writeInt(int std, int num, int radix, int znac)
{
  if (std < 0 && std > 1)
  if (num == 0) {
    write(std, "0", 1);
    return 1;
  }
  
  char sign = '-';

  char buffer[SIZE_BUFFER];
  int counter = SIZE_BUFFER;

  if (radix == 10) {
    if (num < 0) {
      write(std, &sign, 1);
      num = -num;
    }
  }

  while (num) {
    if (num % radix > 9) {
      buffer[--counter] = 'A' + num % radix - 10;
      num /= radix;
    } else {
      buffer[--counter] = '0' + (num % radix);
      num /= radix;
    }
  }
  if (znac > -1) {
    if (counter < znac) {
      znac = znac - counter;
      while (znac) {
        write(std, "0", 1);
        znac--;
      }
    }
  }
  write(std, &buffer[counter], SIZE_BUFFER - counter);
  return counter;
}
