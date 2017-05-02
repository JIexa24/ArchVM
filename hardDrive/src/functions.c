/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/hardDrive.h"

extern unsigned int countCylinder;
extern unsigned int countHead;
extern unsigned int countSector;

int initIdesh(tIDECHS* geometry) {
  char buffer[SIZE_BUFFER];

  unsigned int tmp;
  int i = 0;

  writeChar(1, "countCylinder\n");
  do {
    read(1, &buffer[i++], 1);
  } while (buffer[i - 1] != '\n');
  buffer[i - 1] = '\0';
  sreadInt(buffer, &tmp, 10);
  geometry->countCylinder = tmp;
  i = 0;

  writeChar(1, "countHead\n");
  do {
    read(1, &buffer[i++], 1);
  } while (buffer[i - 1] != '\n');
  buffer[i - 1] = '\0';
  sreadInt(buffer, &tmp, 10);
  geometry->countHead = tmp;
  i = 0;

  writeChar(1, "countSector\n");
  do {
    read(1, &buffer[i++], 1);
  } while (buffer[i - 1] != '\n');
  buffer[i - 1] = '\0';
  sreadInt(buffer, &tmp, 10);
  geometry->countSector = tmp;

  return 0;
}

