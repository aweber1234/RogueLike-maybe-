#include "components.h"
#include "ecs.h"
#include "functions.h"
#include "sharedData.h"
#include <ncursesw/ncurses.h>

void PlayerInit(EntityMeta *player, EntitiesData *data)
{
  ComponentColumn *positionColumn = GetComponentColumn(data, player, POSITION_MASK);
  ComponentColumn *symbolColumn = GetComponentColumn(data, player, SYMBOL_MASK);
  if (positionColumn == NULL || symbolColumn == NULL)
  {
    fprintf(debugOut,
            "(PlayerInit) NULL pointer for symbol or position columns!");
    fflush(debugOut);
    return;
  }

  Symbol *symbol = &((Symbol *)symbolColumn->entityRow)[player->rowIndex];
  Position *position = &((Position *)positionColumn->entityRow)[player->rowIndex];

  position->x = MAP_COLS / 2;
  position->y = MAP_LINES / 2;
  symbol->value = L'☻';
}
