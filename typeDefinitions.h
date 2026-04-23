#pragma once
#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

#include <ncursesw/ncurses.h>

// type definitions
//___________________________________________________________

typedef enum
{
  NONE,
  WALL,
  OPEN
} TileType;

typedef struct
{
  int xPos, yPos;
  wchar_t symbol;
} Player;

typedef struct
{
  int xPos, yPos;
  wchar_t symbol;
  TileType type;
} Tile;

typedef struct
{
  int xPos, yPos, width, height;
}Room;

typedef struct
{
  int width, height, size, roomsAmt;
  Tile *tiles;
  Room *rooms;
} GameMap;

typedef struct
{
  void *componentEntries;
  size_t componentTypeSize;
  int highestComponentIndex;
  int freeSpotsIndex;
  int freeSpots[256];
  int nextIndex;
} ComponentsData;


#endif
