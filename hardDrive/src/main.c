#include "./../include/hardDrive.h"

int main(int argc, char** argv)
{
  char buffer[SIZE_BUFFER];

  tIDECHS geometry;
  unsigned int tmp;
  int i = 0;

  writeChar(1, "countCylinder\n");
  do {
    read(1,&buffer[i++],1);
  } while (buffer[i - 1] != '\n');
  buffer[i - 1] = '\0';
  sreadInt(buffer, &tmp, 10);
  geometry.countCylinder = tmp;

  writeChar(1, "countHead\n");
  do {
    read(1,&buffer[i++],1);
  } while (buffer[i - 1] != '\n');
  buffer[i - 1] = '\0';
  sreadInt(buffer, &tmp, 10);
  geometry.countHead = tmp;

  writeChar(1, "countSector\n");
  do {
    read(1,&buffer[i++],1);
  } while (buffer[i - 1] != '\n');
  buffer[i - 1] = '\0';
  sreadInt(buffer, &tmp, 10);
  geometry.countSector = tmp;

  return 0;
}
