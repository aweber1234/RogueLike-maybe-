#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ncursesw/ncurses.h>
#include "typeDefinitions.h"



//function declarations-------------------------------------------

//map functions
void InitializeMap(GameMap *map, int width, int height);
void GenerateMap(GameMap *map, int minRooms, int maxRooms, int minRoomSize, int maxRoomSize);
void MakeRoom(GameMap *map, int xPos, int yPos, int width, int height);
void MakeHall(GameMap *map, int xstart, int ystart, int xend, int yend);
void ConnectRooms(GameMap *map);

//draw functions
void DrawTile(WINDOW *mapWin, Tile *tile);
void DrawPlayer(WINDOW *mapWin, Player *player);
void DrawMap(WINDOW *thisWin, GameMap *map);

//player functions
void MovePlayer(Player *player, int moveX, int moveY, GameMap *map, WINDOW *mapWin);
void PlayerInit(Player *player, GameMap *map);


//game setup functions
void SetWindows(WINDOW *baseWin, WINDOW *mapWin);

//tool functions
int RandRange(int n);

//IntList functions
IntList IntListConstruct();
int IntListResize(IntList *list, int newSize);
void IntListAdd(IntList *list, int item);
void IntListRemove(IntList *list, int itemIndex);

//smart storage functions
void SmartStorageInitialize(SmartStorage *data, int storageTypeSize);
int SmartStorageNextIndex(SmartStorage *data);
void SmartStorageRemoveAt(SmartStorage *data, int index);

#endif
