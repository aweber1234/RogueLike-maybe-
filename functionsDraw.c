#include "functions.h"
#include "typeDefinitions.h"
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>


void DrawMap(WINDOW *mapWin, GameMap *map)
{
  for (int i = 0; i < map->size; i++)
  {
    DrawTile(mapWin, &map->tiles[i]);
  }
}

void DrawTile(WINDOW *mapWin, Tile *tile)
{
  cchar_t toDraw;
  setcchar(&toDraw, &tile->symbol, 0, 0, NULL);
  mvwadd_wch(mapWin, tile->yPos, tile->xPos, &toDraw);
}

void DrawPlayer(WINDOW *mapWin, Player *player)
{
  cchar_t toDraw;
  setcchar(&toDraw, &player->symbol, 0, 0, NULL);
  mvwadd_wch(mapWin, player->yPos, player->xPos, &toDraw);
}
