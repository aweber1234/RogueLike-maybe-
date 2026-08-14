#pragma once
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <ncursesw/ncurses.h>
#include "typeDefinitions.h"

//component bitmasks
//___________________________________________________________
#define POSITION_MASK (1 << 0)
#define SIZE_MASK (1 << 1)
#define HEALTH_MASK (1 << 2)
#define SYMBOL_MASK (1 << 3)
#define AGILITY_MASK (1 << 4)
#define STRENGTH_MASK (1 << 5)
#define WEIGHT_MASK (1 << 6)



// type definitions
//___________________________________________________________


typedef struct
{
  int *maskData;
  SmartStorage maskSS;
} ComponentDataMask;


typedef struct
{
  int x, y, z;
} Position;

typedef struct
{
  Position *positionComps;
  SmartStorage positionSS;
} ComponentDataPosition;

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
  Health *healthComps;
  SmartStorage healthSS;
} ComponentDataHealth;

typedef struct
{
  int value;
} Agility;

typedef struct
{
  Agility *agilityComps;
  SmartStorage agilitySS;
} ComponentDataAgility;

typedef struct
{
  int value;
} Strength;

typedef struct
{
  Strength *strengthComps;
  SmartStorage strengthSS;
} ComponentDataStrength;

typedef struct
{
  int value;
} Weight;

typedef struct
{
  Weight *weightComps;
  SmartStorage weightSS;
} ComponentDataWeight;

typedef struct
{
  wchar_t value;
} Symbol;

typedef struct
{
  Symbol *symbolComps;
  SmartStorage symbolSS;
} ComponentDataSymbol;



#endif
