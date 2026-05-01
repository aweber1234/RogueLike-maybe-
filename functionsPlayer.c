#include "functions.h"
#include "typeDefinitions.h"
#include <ncursesw/ncurses.h>


void PlayerInit(Player *player, GameMap *map)
{
  player->xPos = map->width / 2;
  player->yPos = map->height / 2;
  player->symbol = L'☻';
}

void MovePlayer(Player *player, int moveX, int moveY, GameMap *map,
                WINDOW *mapWin)
{
  int newX = player->xPos + moveX;
  int newY = player->yPos + moveY;
  int index = (newY * map->width) + newX;

  if (newX < map->width && newY < map->height && newX >= 0 && newY >= 0 &&
    (map->tiles[index].type != WALL))
  {
    int oldX = player->xPos;
    int oldY = player->yPos;

    player->xPos = newX;
    player->yPos = newY;

    DrawPlayer(mapWin, player);

    DrawTile(mapWin, &map->tiles[(oldY * map->width) + oldX]);

    wnoutrefresh(mapWin);
  }
}


