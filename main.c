#include "functions.h"
#include "typeDefinitions.h"
#include "sharedData.h"
#include <locale.h>
#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <stdlib.h>


FILE *debugOut = NULL;

int main()
{
  debugOut = fopen("errors.txt", "w");
  GameMap map;
  map.width = 100;
  map.height = 30;
  map.size = map.width * map.height;
  map.tiles = (Tile *)malloc(sizeof(Tile) * map.size);

  Player player;
  player.xPos = map.width / 2;
  player.yPos = map.height / 2;
  player.symbol = L'☻';

  WINDOW *mapWin;

  InitializeMapArray(&map);
  //MakeRoom(&map, (map.width / 2) - 3, (map.height / 2) - 3, 6, 6);
  GenerateMap(&map, 12, 12);

  setlocale(LC_ALL, "");
  initscr(); /* Start curses mode 		*/
  raw();     /* Line buffering disabled	*/
  noecho();  /* Don't echo() while we do getch */
  keypad(stdscr, TRUE);
  curs_set(0);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);

  wattron(stdscr, COLOR_PAIR(1));
  box(stdscr, 0, 0);
  refresh();

  mapWin = derwin(stdscr, LINES - 2, COLS - 2, 1, 1);

  DrawMap(mapWin, &map);
  DrawPlayer(mapWin, &player);
  wrefresh(mapWin);

  int result = 0;

  while ((result = getch()) != 'q')
  {
    switch (result)
    {
    case KEY_UP:
      MovePlayer(&player, 0, -1, &map, mapWin);
      break;
    case KEY_DOWN:
      MovePlayer(&player, 0, 1, &map, mapWin);
      break;
    case KEY_LEFT:
      MovePlayer(&player, -1, 0, &map, mapWin);
      break;
    case KEY_RIGHT:
      MovePlayer(&player, 1, 0, &map, mapWin);
      break;
    default:
      if (result == KEY_RESIZE)
      {
        erase();
        box(stdscr, 0, 0);

        // werase(myWin);
        wresize(mapWin, LINES - 2, COLS - 2);
        DrawMap(mapWin, &map);
        DrawPlayer(mapWin, &player);
        wnoutrefresh(stdscr);
        wnoutrefresh(mapWin);
      };
      break;
    }
    doupdate();
  }

  delwin(mapWin);
  endwin(); /* End curses mode		  */
  fclose(debugOut);
  return 0;
}
