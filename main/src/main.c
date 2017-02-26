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
  int exit = 0;
  int refreshFlg = 0;
  enum keys key;
  
  sc_regSet(FLAG_INTERRUPT, 1);

  if ((fd = open("ascibig", O_RDONLY)) == -1) {
    writeChar(2,"Cannot open ascibig\n");
    return -1;
  }
  bc_bigcharread(fd, bigChars, 128, &cn);
  close(fd);
  setSignals();
  mt_clrscr();

  sc_commandEncode(0x10, 50, &tmp);
  sc_memorySet(0, tmp);
  sc_memorySet(1, 2);
  
  while (!exit) {
    if (!refreshFlg)
      refreshGui(position);

    rk_readkey(&key);

    if(BITCHECK(sc_register,FLAG_INTERRUPT)) {
      switch (key) {
        case KEY_up:
          if (cursorY != 0)
            cursorY--;
          else
            cursorY = 9;
          refreshFlg = 0;
        break;

        case KEY_down:
          cursorY = (cursorY + 1) % 10;
          refreshFlg = 0;
        break;

        case KEY_left:
          if (cursorX != 0)
            cursorX--;
          else
            cursorX = 9;
          refreshFlg = 0;
        break;

        case KEY_right:
          cursorX = (cursorX + 1) % 10;
          refreshFlg = 0;
        break;

        case KEY_f5:
          refreshFlg = changeAccumulator(position);
        break;

        case KEY_f6:
          refreshFlg = changeInstRegisterCount(position);
        break;
	
        case KEY_enter:
          refreshFlg = changeCell(position);
        break;
					
        case KEY_t:
          timerHand(SIGALRM);
		  position = instructionRegisterCount;
          cursorX = instructionRegisterCount / 10;
          cursorY = instructionRegisterCount % 10;
        break;

        case KEY_s:
          memorySave(position);
          refreshFlg = 1;
        break;

        case KEY_l:
          memoryLoad(position);
          refreshFlg = 1;
        break;
      }
    }
    if (key == KEY_q)
      exit = 1;
    else if (key == KEY_i) {
      instructionRegisterCount = 0;
      position = 0;
      cursorX = 0;
      cursorY = 0;
    } else if (key == KEY_r) {
      if (BITCHECK(sc_register, FLAG_INTERRUPT)) {
        sc_regSet(FLAG_INTERRUPT, 0);
        timerHand(SIGALRM);
      } else {
        alarm(0);
        sc_regSet(FLAG_INTERRUPT, 1);
        position = instructionRegisterCount;
        cursorX = instructionRegisterCount / 10;
        cursorY = instructionRegisterCount % 10;
        refreshGui(position);
	  }
    }
    position = cursorY + cursorX * 10;
  }
}
