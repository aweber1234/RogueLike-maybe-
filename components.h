#pragma once
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <ncursesw/ncurses.h>


// type definitions
//___________________________________________________________

typedef enum
{
  POSITION_COMPONENT,
  HEALTH_COMPONENT,
  WEIGHT_COMPONENT,
  AGILITY_COMPONENT,
  STRENGTH_COMPONENT,
  SYMBOL_COMPONENT,
  COMPONENT_TYPE_COUNT
} COMPONENT_TYPE;

typedef struct
{
  int x, y, z;
} Position;

typedef struct
{
  int width, height;
} Size;

typedef struct
{
  int value;
} Health;

typedef struct
{
  int value;
} Agility;

typedef struct
{
  int value;
} Strength;

typedef struct
{
  int value;
} Weight;

typedef struct
{
  wchar_t value;
} Symbol;


#endif
