#include "components.h"
#include "ecs.h"
#include "functions.h"
#include "sharedData.h"
#include "typeDefinitions.h"
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

void DrawMap(GameMap *map)
{
  for (int i = 0; i < map->size; i++)
  {
    DrawTile(&map->tiles[i]);
  }
}

void DrawTile(Tile *tile)
{
  cchar_t toDraw;
  setcchar(&toDraw, &tile->symbol, 0, 0, NULL);
  mvwadd_wch(mapWin, tile->yPos, tile->xPos, &toDraw);
}

void DrawPlayer(EntitiesData *data, EntityMeta *player)
{
  ComponentColumn *symbolColumn = GetComponentColumn(data, player, SYMBOL_MASK);
  ComponentColumn *positionColumn =
      GetComponentColumn(data, player, POSITION_MASK);

  if (symbolColumn == NULL || positionColumn == NULL)
  {
    fprintf(debugOut, "DrawTile) NULL pointer for symbol or position columns!");
    return;
  }

  Symbol *symbol = &((Symbol *)symbolColumn->entityRow)[player->rowIndex];
  Position *position = &((Position *)positionColumn->entityRow)[player->rowIndex];

  cchar_t toDraw;
  setcchar(&toDraw, &symbol->value, 0, 0, NULL);
  mvwadd_wch(mapWin, position->y, position->x, &toDraw);
}
