/*
Created by JIexa24 (Alexey R.)
*/
#include "./../include/hardDrive.h"

int main(int argc, char** argv)
{
  double sizeDisc           = 0;
  double tmpSizeDisc        = 0;
  double sizePart           = -1;
  char sizeDsc[SIZE_BUFFER] = {0};
  char buffer[SIZE_BUFFER]  = {0};
  char active               = 'n';
  char flgactive            = 0;
  char typeOfPart           = 0;
  char enter                = 0;
  int i                     = 0;
  int indPart               = 0;
  int tmpIndPart            = 0;

  tPartitionTable* table = malloc(sizeof(tPartitionTable) * (indPart + 1));
  tIDECHS chs;
  initIdesh(&chs);
  printf("%u %u %u\n",chs.countCylinder,chs.countHead ,chs.countSector  );
  sizeDisc = chs.countCylinder * chs.countHead * chs.countSector * 512;
  sizeDisc = sizeDisc / (1024 * 1024);

  sprintf(sizeDsc,"%.12lf", sizeDisc);
  tmpSizeDisc = sizeDisc;
  while (1) {
    writeChar(1, "\nFree Size Disc(Gb): ");
    sprintf(buffer, "%lf", tmpSizeDisc);
    writeChar(1, buffer);
    writeChar(1, "\n");

    while (sizePart < 0 ) {
      i = 0;
      writeChar(1,"Please, input size of part: ");
      do {
        read(0, &buffer[i++], 1);
      } while (buffer[i - 1] != '\n');
      buffer[i - 1] = '\0';
      sscanf(buffer,"%lf", &sizePart);
    }
    if (sizePart <= 0) {
      break;
    }
    while (!(typeOfPart < '4' & typeOfPart > '0')) {
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
      active == 'y' ? flgactive = 1 : ((active == 'n') ? (flgactive = 0) :
                                                         (flgactive = -1));
      if (flgactive == 0)
        break;
      tmpIndPart = 0;
    }


    tmpSizeDisc = tmpSizeDisc - sizePart;
    if (tmpSizeDisc < 0) {
      break;
    }
    table[indPart].flagActive = active;
    table[indPart].size = sizePart;
    table[indPart].fileSystem = typeOfPart;

    typeOfPart = 0;
    active     = 'n';
    sizePart   = -1;
    indPart++;
    table = realloc(table, sizeof(*table) * (indPart + 1));
  }
  writeChar(1, "\n\n");
  while (1) {
    writeChar(1, "Part: ");
    sprintf(buffer,"%lf",table[tmpIndPart].size);
    writeChar(1, buffer);
    writeChar(1, "\n");

    writeChar(1, "Type: ");
    switch(table[tmpIndPart].fileSystem - '0') {
      case 1:
        writeChar(1, "Ext\n");
      break;
      case 2:
        writeChar(1, "NTFS\n");
      break;
      case 3:
        writeChar(1, "Linux_swap\n");
      break;
      default:
        writeChar(1, "\n");
      break;
    }

    writeChar(1, "Active:");
    char c = table[tmpIndPart].flagActive;
    write(1, &c, 1);
    writeChar(1, "\n");
    writeChar(1, "\n");
    tmpIndPart++;
    if (tmpIndPart >= indPart) {
      break;
    }
  }

  free(table);
  return 0;
}
