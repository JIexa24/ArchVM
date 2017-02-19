#include "./../include/writeInt.h"

#define SIZE_BUFFER 100

int writeInt(int num)
{
  if (num == 0) {
    write(1, "0", 1);
    return 1;
  }
  char buffer[SIZE_BUFFER];
  char sign = '-';

  if (num < 0) {
    write(1, &sign, 1);
    num = -num;
  }

  int counter = SIZE_BUFFER;

  while (num) {
    buffer[--counter] = '0' + (num % 10);
    num /= 10;
  }

  write(1, &buffer[counter], SIZE_BUFFER - counter);
  return counter;
}
/*------------------------------------------------------------------------------*/
int writeIntHex(int num)
{
  if (num == 0) {
    write(1, "0", 1);
    return 1;
  }

  char buffer[SIZE_BUFFER];
  int counter = SIZE_BUFFER;
  
  while (num) {
    if (num % 16 > 9) {
      switch(num % 16) {
        case 10:
          buffer[--counter] = 'A';
        break;
        case 11:
          buffer[--counter] = 'B';
        break;
        case 12:
          buffer[--counter] = 'C';
        break;
        case 13:
          buffer[--counter] = 'D';
        break;
        case 14:
          buffer[--counter] = 'E';
        break;
        case 15:
          buffer[--counter] = 'F';
        break;
      }
      num /= 16;
    } else {
      buffer[--counter] = '0' + (num % 16);
      num /= 16;
    }
  }
  write(1, &buffer[counter], SIZE_BUFFER - counter);
  return counter;
}
