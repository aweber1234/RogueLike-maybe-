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

typedef enum
{
  LEFT,
  RIGHT,
  UP,
  DOWN
}Direction;

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
  int width, height, size;
  Tile *tiles;

} GameMap;

#endif
