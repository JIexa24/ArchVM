#include "./../include/writeInt.h"

#define SIZE_BUFFER 100
/*
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
int writeInt(int num, int radix)
{
  if (num == 0) {
    write(1, "0", 1);
    return 1;
  }
  
  char sign = '-';

  char buffer[SIZE_BUFFER];
  int counter = SIZE_BUFFER;

  if (radix == 10) {
    if (num < 0) {
      write(1, &sign, 1);
      num = -num;
    }
  }

  while (num) {
    if (num % radix > 9) {
      switch(num % radix) {
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
      num /= radix;
    } else {
      buffer[--counter] = '0' + (num % radix);
      num /= radix;
    }
  }
  write(1, &buffer[counter], SIZE_BUFFER - counter);
  return counter;
}
