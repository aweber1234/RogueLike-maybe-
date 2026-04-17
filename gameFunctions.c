#include "functions.h"
#include "sharedData.h"
#include "typeDefinitions.h"
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

void InitializeMapArray(GameMap *map)
{
  for (int x = 0; x < map->width; x++)
  {
    for (int y = 0; y < map->height; y++)
    {
      int index = (y * map->width) + x;
      map->tiles[index].symbol = L' ';
      map->tiles[index].type = NONE;
      map->tiles[index].xPos = x;
      map->tiles[index].yPos = y;
    }
  }
}

void GenerateMap(GameMap *map, int minRooms, int maxRooms)
{
  if (minRooms < 1)
  {
    minRooms = 1;
  }
  if (maxRooms > 10)
  {
    maxRooms = 10;
  }

  srand(time(0));
  int roomsAmt = RandRange(maxRooms - minRooms) + minRooms;
  int roomX[roomsAmt];
  int roomY[roomsAmt];
  int roomWidth[roomsAmt];
  int roomHeight[roomsAmt];
  int minRoomSize = 7;
  int maxRoomSize = 14;

  int maxxPosition = map->width - minRoomSize;
  int maxyPosition = map->height - minRoomSize;

  fprintf(debugOut, "\nroomsAmt:%d  minRoomSize:%d  maxRoomSize:%d\n", roomsAmt,
          minRoomSize, maxRoomSize);

  for (int i = 0; i < roomsAmt; i++)
  {
    int x = RandRange(maxxPosition);
    int y = RandRange(maxyPosition);

    int maxRoomWidth = map->width - x;
    int maxRoomHeight = map->height - y;

    int width = RandRange(maxRoomSize - minRoomSize) + minRoomSize;
    int height = RandRange(maxRoomSize - minRoomSize) + minRoomSize;

    if (width > maxRoomWidth)
    {
      width = maxRoomWidth;
    }
    if (height > maxRoomHeight)
    {
      height = maxRoomHeight;
    }

    roomX[i] = x;
    roomY[i] = y;
    roomWidth[i] = width;
    roomHeight[i] = height;

    fprintf(debugOut,
            "  x:%d  y:%d  width:%d  height:%d\n  maxRoomWidth:%d  "
            "maxRoomHeight:%d\n",
            x, y, width, height, maxRoomWidth, maxRoomHeight);
    MakeRoom(map, x, y, width, height);
  }

  for (int i = 0; i < roomsAmt - 1; i++)
  {
    MakeHall(map,
             roomX[i] + (roomWidth[i] / 2),
             roomY[i] + (roomHeight[i] / 2),
             roomX[i + 1] + (roomWidth[i + 1] / 2),
             roomY[i + 1] + (roomHeight[i + 1] / 2));
  }
}

void DrawMap(WINDOW *mapWin, GameMap *map)
{
  for (int i = 0; i < map->size; i++)
  {
    DrawTile(mapWin, &map->tiles[i]);
  }
}

void MakeHall(GameMap *map, int xstart, int ystart, int xend, int yend)
{
  int xdif = (xend - xstart);
  int ydif = (yend - ystart);

  int xmod = 1;
  int ymod = 1;
  if (xdif < 0)
  {
    xmod = -1;
  }
  if (ydif < 0)
  {
    ymod = -1;
  }

  int absxdif = abs(xdif);
  int absydif = abs(ydif);

  for (int i = 0; i < absxdif; i++)
  {
    MakeRoom(map, xstart + (i * xmod), ystart, 3, 3);
    // fprintf(debugOut, "x hall start:(x:%d, y:%d)\n",x,y);
  }
  for (int i = 0; i < absydif; i++)
  {

    MakeRoom(map, xend, ystart + (i * ymod), 3, 3);
    // fprintf(debugOut, "y hall start:(x:%d, y:%d)\n",x,y);
  }
}

void MakeRoom(GameMap *map, int xPos, int yPos, int width, int height)
{
  if (xPos + width <= map->width && xPos >= 0 && yPos + height <= map->height &&
      yPos >= 0)
  {
    for (int x = xPos; x < xPos + width; x++)
    {
      for (int y = yPos; y < yPos + height; y++)
      {
        int index = (y * map->width) + x;
        if ((x == xPos || y == yPos || x == xPos + width - 1 ||
             y == yPos + height - 1) &&
            map->tiles[index].type != OPEN)
        {
          map->tiles[index].symbol = L'█';
          map->tiles[index].type = WALL;
        }
        else
        {
          map->tiles[index].symbol = L'┼';
          map->tiles[index].type = OPEN;
        }
        map->tiles[index].xPos = x;
        map->tiles[index].yPos = y;
      }
    }
  }
  else
  {
    fprintf(debugOut, "Room does not fit within map dimensions!\n");
  }
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
