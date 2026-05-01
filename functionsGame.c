#include "sharedData.h"
#include <ncursesw/ncurses.h>


void SetWindows(WINDOW *baseWin, WINDOW *mapWin)
{
  wresize(stdscr, TOTAL_LINES, TOTAL_COLS);
  box(stdscr,0 ,0 );
  wresize(baseWin, MAP_LINES + 2, MAP_COLS + 2);
  box(baseWin, 0, 0);
  wresize(mapWin, MAP_LINES, MAP_COLS);
}



