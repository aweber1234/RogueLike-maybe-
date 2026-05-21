#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "ecs.h"
#include "typeDefinitions.h"
#include <ncursesw/ncurses.h>

// function declarations-------------------------------------------

// ecs functions
EntityTable* GetArchetypeTable(EntitiesData *data, uint16_t archetypeMask);
bool ArchetypeExists(EntitiesData *entities, uint16_t archetypeMask);
bool EntityHasComponent(EntityMeta *entity, uint16_t componentMask);
void InitializeEntitiesData(EntitiesData *entities);
int IncreaseArchetypeTablesSize(EntitiesData *entities, uint16_t increaseBy);
void SetArchetypeTable(EntityTable *table, uint16_t archetypeMask);
int MakeArchetype(EntitiesData *entities, uint16_t archetypeMask);
int IncreaseEntityTableCapacity(EntityTable *table, uint16_t increaseBy);
ComponentColumn *GetComponentColumn(EntitiesData *data, EntityMeta *entity, uint16_t componentMask);
EntityMeta *MakeEntity(EntitiesData *entities, uint16_t archetypeMask);

// map functions
void InitializeMap(GameMap *map, int width, int height);
void GenerateMap(GameMap *map, int minRooms, int maxRooms, int minRoomSize,
                 int maxRoomSize);
void MakeRoom(GameMap *map, int xPos, int yPos, int width, int height);
void MakeHall(GameMap *map, int xstart, int ystart, int xend, int yend);
void ConnectRooms(GameMap *map);

// draw functions
void DrawTile(WINDOW *mapWin, Tile *tile);
void DrawPlayer(WINDOW *mapWin, EntitiesData *data, EntityMeta *player);
void DrawMap(WINDOW *thisWin, GameMap *map);

// player functions
void PlayerInit(EntityMeta *player, EntitiesData *data);

// game operation
void NextGameTurn();
void MoveEntity(EntityMeta *entity, int moveX, int moveY, GameMap *map,
                WINDOW *mapWin, EntitiesData *data);

// game setup
void SetWindows(WINDOW *baseWin, WINDOW *mapWin);

// tool functions
int RandRange(int n);
void *VoidIndexTo(void *start, int index, size_t typeSize);

// IntList functions
IntList IntListConstruct();
int IntListResize(IntList *list, int newSize);
void IntListAddItem(IntList *list, int item);
void IntListRemove(IntList *list, int itemIndex);
void IntListRemoveFast(IntList *list, int itemIndex);

// smart storage functions
void SmartStorageInitialize(SmartStorage *data, int storageTypeSize);
int SmartStorageNextIndex(SmartStorage *data);
void SmartStorageRemoveAt(SmartStorage *data, int index);

#endif
