#pragma once
#include "components.h"
#ifndef ENTITY_H
#define ENTITY_H

#include <ncursesw/ncurses.h>

// type definitions
//___________________________________________________________

typedef struct
{
  void *components[(int)COMPONENT_TYPE_COUNT];
} Entity;

#endif
