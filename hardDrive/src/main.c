/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/hardDrive.h"

extern unsigned int countCylinder;
extern unsigned int countHead;
extern unsigned int countSector;

int main(int argc, char** argv)
{
  double sizeDisc;
  tIDECHS geometry;
  printf("\n%u %u %u",geometry.countCylinder,geometry.countHead,geometry.countSector);
  initIdesh(&geometry);
  printf("\n%u %u %u",geometry.countCylinder,geometry.countHead,geometry.countSector);

  tCHS chs;
  printf("\n%u %u %u",chs.countCylinder,chs.countHead,chs.countSector);
  g_idechs2chs(geometry, &chs);
  printf("\n%u %u %u",chs.countCylinder,chs.countHead,chs.countSector);

  sizeDisc = chs.countCylinder * chs.countHead * chs.countSector;
  sizeDisc = sizeDisc / (1024 * 1024);

  char buf[SIZE_BUFFER];
  sprintf(buf,"%.12lf", sizeDisc);

  writeChar(1, "\nSize Disc(Gb): ");
  writeChar(1, buf);
  writeChar(1, "\n");

  return 0;
}
