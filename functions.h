#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ncursesw/ncurses.h>
#include "typeDefinitions.h"

#pragma once

//function declarations
//___________________________________________________________

void DrawMap(WINDOW *thisWin, MapType *map);
void MovePlayer(Player *player, int moveX, int moveY, MapType *map, WINDOW *mapWin);
void DrawTile(WINDOW *mapWin, TileType *tile);
void DrawPlayer(WINDOW *mapWin, Player *player);


#endif
