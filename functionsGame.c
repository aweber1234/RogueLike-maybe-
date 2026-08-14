#include "components.h"
#include "ecs.h"
#include "functions.h"
#include "sharedData.h"
#include <ncursesw/ncurses.h>

void SetWindows()
{
  wresize(stdscr, TOTAL_LINES, TOTAL_COLS);
  box(stdscr, 0, 0);
  wresize(topWin, MAP_LINES + 2, MAP_COLS + 2);
  box(topWin, 0, 0);
  wresize(mapWin, MAP_LINES, MAP_COLS);
}





void MoveEntity(EntityMeta *entity, int moveX, int moveY, GameMap *map,
                EntitiesData *data)
{
  ComponentColumn *positionColumn =
      GetComponentColumn(data, entity, POSITION_MASK);

  if (positionColumn == NULL)
  {
    fprintf(debugOut, "DrawTile) NULL pointer for position column!");
    return;
  }

  Position *position =
      &((Position *)positionColumn->entityRow)[entity->rowIndex];

  int newX = position->x + moveX;
  int newY = position->y + moveY;
  int index = (newY * map->width) + newX;

  if (newX < map->width && newY < map->height && newX >= 0 && newY >= 0 &&
      (map->tiles[index].type != WALL))
  {
    int oldX = position->x;
    int oldY = position->y;

    position->x = newX;
    position->y = newY;

    DrawPlayer(data, entity);

    DrawTile(&map->tiles[(oldY * map->width) + oldX]);

    wnoutrefresh(mapWin);
  }

  NextGameTurn();
}

void NextGameTurn() {}
