/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/mainHeader.h"

extern int accumulator;
extern int instructionRegisterCount;
extern int writeUsed;
extern int writeValue;
extern int bigChars[];
extern int SCANPRINTRADIX;

struct itimerval val, oval;

int main(int argc, char** argv)
{
  sc_memoryInit();
  sc_regInit();
  setSignals();
  rk_mytermsave();
  sc_regSet(FLAG_INTERRUPT, 1);

  int cursorX    = 0;
  int cursorY    = 0;
  int position   = 0;
  int fd         = 0;
  int cn         = 0;
  int tmp        = 0;
  int exit       = 0;
  int refreshFlg = 0;
  int regis      = 0;
  int regisProg  = 0;
  enum keys key  = KEY_other;

  val.it_interval.tv_sec = TIMESLEEPSEC;
  val.it_interval.tv_usec = MKR(TIMESLEEPUSEC);
  val.it_value.tv_sec = TIMESLEEPSEC;
  val.it_value.tv_usec = MKR(TIMESLEEPUSEC);

  if ((fd = open("ascibig", O_RDONLY)) == -1) {
    writeChar(2,"Cannot open ascibig\n");
    return -1;
  }
  bc_bigcharread(fd, bigChars, 17, &cn);
  close(fd);

  mt_clrscr();

  refreshGuiSt(position);
  while (!exit) {
    if (!refreshFlg) {
      refreshGui(position);
      refreshFlg = 1;
    }

    rk_readkey(&key);
    sc_regGet(FLAG_INTERRUPT, &regisProg);

    if(regisProg) {
      switch (key) {
        case KEY_up:
          if (cursorY != 0)
            cursorY--;
          else
            cursorY = 9;

          refreshFlg = 0;
          key  = KEY_other;
        break;

        case KEY_down:
          cursorY = (cursorY + 1) % 10;
          refreshFlg = 0;
          key  = KEY_other;
        break;

        case KEY_left:
          if (cursorX != 0)
            cursorX--;
          else
            cursorX = 9;

          refreshFlg = 0;
          key  = KEY_other;
        break;

        case KEY_right:
          cursorX = (cursorX + 1) % 10;
          refreshFlg = 0;
          key  = KEY_other;
        break;

        case KEY_f5:
          refreshFlg = changeAccumulator(position);
          key  = KEY_other;
        break;

        case KEY_f6:
          refreshFlg = changeInstRegisterCount(position);
          key  = KEY_other;
        break;

	      case KEY_x:
          SCANPRINTRADIX = 16;
          refreshFlg = 0;
          key  = KEY_other;
        break;

        case KEY_d:
          SCANPRINTRADIX = 10;
          refreshFlg = 0;
          key  = KEY_other;
        break;

        case KEY_enter:
          if (SCANPRINTRADIX == 10) {
            tmp = SCANPRINTRADIX;
            SCANPRINTRADIX = 16;
            refreshFlg = changeCell(position);
            SCANPRINTRADIX = tmp;
          } else if (SCANPRINTRADIX == 16) {
            refreshFlg = changeCell(position);
          }
          key  = KEY_other;
        break;

        case KEY_t:
          CU();
          refreshGui(instructionRegisterCount);
          position = instructionRegisterCount;
          cursorX = instructionRegisterCount / 10;
          cursorY = instructionRegisterCount % 10;
          key  = KEY_other;
        break;

        case KEY_s:
          memorySave(position);
          refreshFlg = 1;
          key  = KEY_other;
        break;

        case KEY_l:
          memoryLoad(position);
          refreshFlg = 1;
          key  = KEY_other;
        break;

        case KEY_i:
          raise(SIGUSR1);
          refreshFlg = 0;
          cursorX = 0;
          cursorY = 0;
          key  = KEY_other;
        break;

        case KEY_q:
          exit = 1;
          key  = KEY_other;
        break;
      }
    }
    if (key == KEY_c) {
      position = instructionRegisterCount;
      cursorX = instructionRegisterCount / 10;
      cursorY = instructionRegisterCount % 10;
      refreshFlg = 0;
      raise(SIGUSR2);
      key  = KEY_other;
    } else if (key == KEY_esc) {
      raise(SIGTERM);
      key  = KEY_other;
    } else if (key == KEY_r) {
      key = KEY_other;
      sc_regGet(FLAG_INTERRUPT, &regis);
      if (regis) {
        sc_regInit();
        setitimer(TIMER, &val, &oval);
        position = instructionRegisterCount;
        cursorX = instructionRegisterCount / 10;
        cursorY = instructionRegisterCount % 10;
        refreshFlg = 0;
        continue;
      } else {
        setitimer(TIMER, NULL, NULL);
        sc_regSet(FLAG_INTERRUPT, 1);
        position = instructionRegisterCount;
        cursorX = instructionRegisterCount / 10 ;
        cursorY = instructionRegisterCount % 10;
        refreshFlg = 0;
        continue;
	    }
    }
    position = cursorY + cursorX * 10;
  }
  rk_mytermrestore();
  signalsRestore();
  setitimer(TIMER, NULL, NULL);
  system("rm -f termsettings");
  return 0;
}
