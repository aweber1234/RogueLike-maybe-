#include "functions.h"
#include "sharedData.h"
#include "typeDefinitions.h"
#include <ncursesw/ncurses.h>
#include <stdlib.h>

void InitializeMap(GameMap *map, int width, int height)
{
  map->width = width;
  map->height = height;
  map->size = width * height;
  map->tiles = (Tile *)malloc(sizeof(Tile) * map->size);

  int index = 0;
  for (int y = 0; y < map->height; y++)
  {
    for (int x = 0; x < map->width; x++)
    {
      map->tiles[index].symbol = L' ';
      map->tiles[index].type = NONE;
      map->tiles[index].xPos = x;
      map->tiles[index].yPos = y;
      index++;
    }
  }
}

void GenerateMap(GameMap *map, int minRooms, int maxRooms, int minRoomSize,
                 int maxRoomSize)
{
  minRooms = minRooms < 1 ? 1 : minRooms;
  maxRooms = maxRooms > 20 ? 20 : maxRooms;
  minRoomSize = minRoomSize < 5 ? 5 : minRoomSize;
  maxRoomSize = maxRoomSize > 25 ? 25 : maxRoomSize;

  int maxxPosition = map->width - minRoomSize;
  int maxyPosition = map->height - minRoomSize;

  map->roomsAmt = RandRange(maxRooms - minRooms) + minRooms;
  map->rooms = (Room *)malloc(sizeof(Room) * map->roomsAmt);

  for (int i = 0; i < map->roomsAmt; i++)
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

    map->rooms[i].xPos = x;
    map->rooms[i].yPos = y;
    map->rooms[i].width = width;
    map->rooms[i].height = height;

    MakeRoom(map, x, y, width, height);
  }

  ConnectRooms(map);
}

void ConnectRooms(GameMap *map)
{
  int startX;
  int startY;
  int endX;
  int endY;

  //connects base rooms
  for (int i = 0; i < map->roomsAmt - 1; i += 2)
  {
    int n = i + 1;
    startX = map->rooms[i].xPos + (map->rooms[i].width / 2);
    startY = map->rooms[i].yPos + (map->rooms[i].height / 2);
    endX = map->rooms[n].xPos + (map->rooms[n].width / 2);
    endY = map->rooms[n].yPos + (map->rooms[n].height / 2);
    MakeHall(map, startX, startY, endX, endY);
  }

  //connects branches to bases
  for (int i = 0; i < map->roomsAmt - 2; i += 2)
  {
    int n = i + 2;
    startX = map->rooms[i].xPos + (map->rooms[i].width / 2);
    startY = map->rooms[i].yPos + (map->rooms[i].height / 2);
    endX = map->rooms[n].xPos + (map->rooms[n].width / 2);
    endY = map->rooms[n].yPos + (map->rooms[n].height / 2);
    MakeHall(map, startX, startY, endX, endY);
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
    for (int y = yPos; y < yPos + height; y++)
    {
      for (int x = xPos; x < xPos + width; x++)
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
