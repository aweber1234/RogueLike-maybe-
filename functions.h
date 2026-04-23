#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ncursesw/ncurses.h>
#include "typeDefinitions.h"



//function declarations
//___________________________________________________________

void InitializeMap(GameMap *map, int width, int height);
void GenerateMap(GameMap *map, int minRooms, int maxRooms, int minRoomSize, int maxRoomSize);
void DrawMap(WINDOW *thisWin, GameMap *map);
void MakeRoom(GameMap *map, int xPos, int yPos, int width, int height);
void MakeHall(GameMap *map, int xstart, int ystart, int xend, int yend);
void ConnectRooms(GameMap *map);

void MovePlayer(Player *player, int moveX, int moveY, GameMap *map, WINDOW *mapWin);
void PlayerInit(Player *player, GameMap *map);
void DrawTile(WINDOW *mapWin, Tile *tile);
void DrawPlayer(WINDOW *mapWin, Player *player);

void SetWindows(WINDOW *baseWin, WINDOW *mapWin);

int RandRange(int n);

#endif
