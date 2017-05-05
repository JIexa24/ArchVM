/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/hardDrive.h"

int main(int argc, char** argv)
{
  double sizeDisc;
  tIDECHS geometry;
  initIdesh(&geometry);

  tCHS chs;
  g_idechs2chs(geometry, &chs);

  sizeDisc = chs.countCylinder * chs.countHead * chs.countSector;
  sizeDisc = sizeDisc / (1024 * 1024);

  char buf[SIZE_BUFFER];
  sprintf(buf,"%.12lf", sizeDisc);

  writeChar(1, "\nSize Disc(Gb): ");
  writeChar(1, buf);
  writeChar(1, "\n");

  return 0;
}
