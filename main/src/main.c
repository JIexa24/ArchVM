#include "./../include/mainHeader.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;
extern int bigChars[];

int main(int argc, char** argv)
{
  sc_memoryInit();
  sc_regInit();

  int cursorX = 0;
  int cursorY = 0;
  int position = 0;
  int fd = 0;
  int cn;
  int tmp = 0;

  if ((fd = open("ascibig", O_RDONLY)) == -1) {
    write(2,"Cannot open ascibig\n", 20);
    return -1;
  }
  mt_clrscr();
  bc_bigcharread(fd, bigChars, 128, &cn);
  close(fd);

  sc_commandEncode(0x10, 126, &tmp);
  sc_memorySet(0, tmp);

  refreshGui(position);
}
