#pragma once
#include <stdint.h>
#define ECS_H
#include <ncursesw/ncurses.h>
// #include "components.h"


/**
 * Each component in a table has a column.
 * Each entity's component is accessed by the entity's row index.
*/
typedef struct
{
  uint16_t componentMask;
  uint16_t columnIndex;
  size_t typeSize;
  size_t typeAlignment;
  void *entityRow;
} ComponentColumn;

/**
 * Includes the metadata for the corresponding entity.
 */
typedef struct
{
  uint16_t archetypeMask;
  int rowIndex;
} EntityMeta;

/**
 * One entity table for each archetype.
 */
typedef struct
{
  uint16_t archetypeMask;
  uint16_t componentsAmount;
  int entitiesCount;
  int entitiesCapacity;
  EntityMeta *entitiesMeta;
  ComponentColumn *componentsColumn;
  /** indexed by the component mask, points to the index on the component collumn array column
   */
} EntityTable;

/**
 * The toatallity of entity and component storage data.
 */
typedef struct
{
  uint16_t tablesCapacity;
  uint16_t tablesCount;
  EntityTable *tables;
  /** indexed by the archetype mask, points to the index on the tables array
   */
  EntityTable **tablePointers;

} EntitiesData;





