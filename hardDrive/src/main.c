/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/hardDrive.h"

int main(int argc, char** argv)
{
  double sizeDisc = 0;
  double sizePart = -1;
  char sizeDsc[SIZE_BUFFER];
  char buffer[SIZE_BUFFER];
  char active     = 0;
  char flgactive  = 0;
  char typeOfPart = 0;
  char enter      = 0;
  int i           = 0;
  int indPart     = 0;

  tPartitionTable table = malloc(sizeof(tPartitionTable));
  tIDECHS geometry;
  initIdesh(&geometry);

  tCHS chs;
  g_idechs2chs(geometry, &chs);

  sizeDisc = chs.countCylinder * chs.countHead * chs.countSector;
  sizeDisc = sizeDisc / (1024 * 1024);

  sprintf(sizeDsc,"%.12lf", sizeDisc);

  while (1) {
    writeChar(1, "\nSize Disc(Gb): ");
    writeChar(1, sizeDsc);
    writeChar(1, "\n");

    while (sizePart < 0) {
	  	writeChar(1,"Please, input size of part: ");
      do {
        read(1, &buffer[i++], 1);
      } while (buffer[i - 1] != '\n');
      buffer[i - 1] = '\0';
      sscanf(buffer,"%lf", &sizePart);
    }

    if (!sizePart) {
      break;
    }

    while (!(typeOfPart < '4' && typeOfPart > '0')) {
	    writeChar(1, "Input type of part:\n");
	    writeChar(1, "\tExt\t=1\n");
	    writeChar(1, "\tNTFS\t=2\n");
	    writeChar(1, "\tLinux_swap\t=3\n");
      read(1, &typeOfPart, 1);
      read(1, &enter, 1);
    }
    while (!(flgactive == 1)) {
      writeChar(1, "This part is active? (y/n):\n");
      read(1, &active, 1);
      read(1, &enter, 1);
      active == 'y' ? flgactive = 1 : ((active == 'n') ? (flgactive = 0) : (flgactive = -1));
    }
    table[indPart].flagActive = flgactive;
    table[indPart].size = sizePart;
    table[indPart].fileSystem = typeOfPart;

    typeOfPart = 0;
    flgactive  = 0;
    active     = 0;
    sizePart   = -1;
    indPart++;
  }
  return 0;
}
