#include "./../include/mainHeader.h"

int main(int argc, char** argv)
{
  int cursor_x = 0;
  int cursor_y = 0;
  int position = 0;

  mt_clrscr();

  sc_memoryInit();
  sc_regInit();

  refreshGui(position);
}
