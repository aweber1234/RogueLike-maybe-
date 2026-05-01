#include "functions.h"
#include "sharedData.h"
#include "typeDefinitions.h"
#include "components.h"
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

int *entities;
SmartStorage entitiesSS;
Position *positionComps;
SmartStorage positionSS;
Health *healthComps;
SmartStorage healthSS;
Weight *weightComps;
SmartStorage weightSS;
Agility *agilityComps;
SmartStorage agilitySS;
Strength *strengthComps;
SmartStorage strengthSS;
Symbol *symbolComps;
SmartStorage symbolSS;

void MakeGuy()
{
  int entityIndex = SmartStorageNextIndex(&entitiesSS);
  entities[entityIndex] = entityIndex;

  SmartStorageNextIndex(&positionSS);
  positionComps[entityIndex].x = MAP_COLS / 2;
  positionComps[entityIndex].y = MAP_LINES / 2;
  SmartStorageNextIndex(&healthSS);
  SmartStorageNextIndex(&weightSS);
  SmartStorageNextIndex(&agilitySS);
  SmartStorageNextIndex(&strengthSS);
  SmartStorageNextIndex(&symbolSS);
}



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

  debugOut = fopen("errors.txt", "w");
  WINDOW *mapWin;
  WINDOW *topWin;
  Player player;
  GameMap map;

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
  PlayerInit(&player, &map);
  DrawMap(mapWin, &map);
  DrawPlayer(mapWin, &player);


  entities = malloc(sizeof(int) * 255);
  SmartStorageInitialize(&entitiesSS, sizeof(int));
  positionComps = malloc(sizeof(Position) * 255);
  SmartStorageInitialize(&positionSS, sizeof(Position));
  healthComps = malloc(sizeof(Health) * 255);
  SmartStorageInitialize(&healthSS, sizeof(Health));
  weightComps = malloc(sizeof(Weight) * 255);
  SmartStorageInitialize(&weightSS, sizeof(Weight));
  agilityComps = malloc(sizeof(Agility) * 255);
  SmartStorageInitialize(&agilitySS, sizeof(Agility));
  strengthComps = malloc(sizeof(Strength) * 255);
  SmartStorageInitialize(&strengthSS, sizeof(Strength));







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

      if (result == KEY_RESIZE && LINES > TOTAL_LINES && COLS > TOTAL_COLS)
      {
        erase();
        SetWindows(topWin, mapWin);
        DrawMap(mapWin, &map);
        DrawPlayer(mapWin, &player);
      };
      break;
    }
    doupdate();
  }

  endwin(); /* End curses mode		  */
  fclose(debugOut);
  return 0;
}
