#include "components.h"
#include "ecs.h"
#include "functions.h"
#include "sharedData.h"
#include "typeDefinitions.h"
#include <locale.h>
#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>


const int BOTTOM_WIN_LINES = 15;
const int MAP_COLS = 100;
const int MAP_LINES = 30;
const int TOTAL_LINES = MAP_LINES + BOTTOM_WIN_LINES + 2;
const int TOTAL_COLS = MAP_COLS + 2;


FILE *debugOut = NULL;


int main()
{
  setlocale(LC_ALL, "");
  initscr(); /* Start curses mode 		*/
  raw();     /* Line buffering disabled	*/
  noecho();  /* Don't echo() while we do getch */
  keypad(stdscr, TRUE);
  curs_set(0);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);

  //debugOut = fopen("errors.txt", "a");
  //fprintf(debugOut, "test\n");
  WINDOW *mapWin;
  WINDOW *topWin;

  GameMap map;
  EntitiesData entitiesData;
  EntityMeta *player;

  refresh();
  wresize(stdscr, TOTAL_LINES, TOTAL_COLS);
  box(stdscr, 0, 0);
  topWin = derwin(stdscr, MAP_LINES + 2, MAP_COLS + 2, 0, 0);
  box(topWin, 0, 0);
  mapWin = derwin(topWin, MAP_LINES, MAP_COLS, 1, 1);
  //wattron(topWin, COLOR_PAIR(1));
  // wrefresh(baseWin);

  InitializeMap(&map, MAP_COLS, MAP_LINES);
  srand(time(0));
  GenerateMap(&map, 10, 10, 1 , 10);
  InitializeEntitiesData(&entitiesData);
  player = MakeEntity(&entitiesData, (POSITION_MASK | SYMBOL_MASK));
  PlayerInit(player, &entitiesData);
  DrawMap(mapWin, &map);
  DrawPlayer(mapWin, &entitiesData, player);







  int result = 0;
  while ((result = getch()) != 'q')
  {
    switch (result)
    {
    case KEY_UP:
      MoveEntity(player, 0, -1, &map, mapWin, &entitiesData);
      break;
    case KEY_DOWN:
      MoveEntity(player, 0, 1, &map, mapWin, &entitiesData);
      break;
    case KEY_LEFT:
      MoveEntity(player, -1, 0, &map, mapWin, &entitiesData);
      break;
    case KEY_RIGHT:
      MoveEntity(player, 1, 0, &map, mapWin, &entitiesData);
      break;
    default:
      break;
    }
    if (result == KEY_RESIZE && LINES > TOTAL_LINES && COLS > TOTAL_COLS)
    {
      erase();
      SetWindows(topWin, mapWin);
      DrawMap(mapWin, &map);
      DrawPlayer(mapWin, &entitiesData, player);
    }
    doupdate();
  }

  endwin(); /* End curses mode		  */
  fclose(debugOut);
  return 0;
}
