#include "functions.h"
#include "typeDefinitions.h"
#include <ncursesw/ncurses.h>
#include <string.h>
#include <wchar.h>

void DrawMap(WINDOW *mapWin, MapType *map)
{
  for (int i = 0; i < map->size; i++)
  {
    DrawTile(mapWin, &map->tiles[i]);
  }
}

void MovePlayer(Player *player, int moveX, int moveY, MapType *map,
                WINDOW *mapWin)
{
  int newX = player->xPos + moveX;
  int newY = player->yPos + moveY;
  if (newX < map->width && newX >= 0 && newY < map->height && newY >= 0)
  {
    int oldX = player->xPos;
    int oldY = player->yPos;

    player->xPos = oldX + moveX;
    player->yPos = oldY + moveY;

    DrawPlayer(mapWin, player);

    DrawTile(mapWin, &map->tiles[(oldY * map->width) + oldX]);

    wnoutrefresh(mapWin);
  }
}

void DrawTile(WINDOW *mapWin, TileType *tile)
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
