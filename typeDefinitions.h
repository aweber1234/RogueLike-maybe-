#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

#include <ncursesw/ncurses.h>

#pragma once

//type definitions
//___________________________________________________________

typedef struct
{
  int xPos, yPos;
  wchar_t symbol;
}Player;

typedef struct
{
  int xPos, yPos;
  wchar_t symbol;
}TileType;

typedef struct
{
  int width, height, size;
  TileType *tiles;

}MapType;



#endif
