#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ncursesw/ncurses.h>
#include "typeDefinitions.h"



//function declarations
//___________________________________________________________

void InitializeMapArray(GameMap *map);
void GenerateMap(GameMap *map, int minRooms, int maxRooms);
void DrawMap(WINDOW *thisWin, GameMap *map);
void MovePlayer(Player *player, int moveX, int moveY, GameMap *map, WINDOW *mapWin);
void DrawTile(WINDOW *mapWin, Tile *tile);
void DrawPlayer(WINDOW *mapWin, Player *player);
void MakeRoom(GameMap *map, int xPos, int yPos, int width, int height);
void MakeHall(GameMap *map, int xstart, int ystart, int xend, int yend);

int RandRange(int n);


#endif
