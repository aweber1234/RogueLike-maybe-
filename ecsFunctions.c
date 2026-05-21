#include "components.h"
#include "ecs.h"
#include "functions.h"
#include "sharedData.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

EntityMeta *MakeEntity(EntitiesData *entities, uint16_t archetypeMask)
{
  if (!ArchetypeExists(entities, archetypeMask))
  {
    MakeArchetype(entities, archetypeMask);
    // fprintf(debugOut, "made archetype for new entity\n");
    // fflush(debugOut);
  }

  EntityTable *table = GetArchetypeTable(entities, archetypeMask);

  if (table->entitiesCapacity == table->entitiesCount)
  {
    int r = IncreaseEntityTableCapacity(table, 256);
    if (!r)
    {
      fprintf(debugOut,
              "(MakeEntity) Error increasing entity table capacity!\n");
      fflush(debugOut);
      return NULL;
    }
    // fprintf(debugOut, "(MakeEntity) Increased table capacity for new
    // entity\n"); fflush(debugOut);
  }

  int entityIndex = table->entitiesCount;

  table->entitiesMeta[entityIndex].rowIndex = entityIndex;
  table->entitiesMeta[entityIndex].archetypeMask = archetypeMask;
  table->entitiesCount++;

  return &table->entitiesMeta[entityIndex];
}

void DeleteEntity(EntitiesData *entities, EntityMeta *entity)
{
  EntityTable *table = GetArchetypeTable(entities, entity->archetypeMask);
  int entityIndex = entity->rowIndex;
  int lastIndex = table->entitiesCount - 1;

  if (entityIndex == lastIndex)
  {
    for (int i = 0; i < table->componentsAmount; i++)
    {
      ComponentColumn *column = &table->componentsColumn[i];
      size_t typeSize = column->typeSize;
      void *old = VoidIndexTo(column[i].entityRow, lastIndex, typeSize);
      void *new = VoidIndexTo(column[i].entityRow, entityIndex, typeSize);
      memcpy(new, old, typeSize);
    }
  }
  table->entitiesCount--;
}

/**
 * Increases the maximum amount of entities in an entity table.
 */
int IncreaseEntityTableCapacity(EntityTable *table, uint16_t increaseBy)
{
  int compCount = table->componentsAmount;
  int newCapacity = table->entitiesCapacity + increaseBy;
  void *tempCol[compCount];

  for (int i = 0; i < compCount; i++)
  {
    tempCol[i] = realloc(table->componentsColumn[i].entityRow,
                         table->componentsColumn[i].typeSize * newCapacity);
    if (tempCol[i] == NULL)
    {
      fprintf(debugOut, "(IncreaseEntityTableCapacity) NULL pointer from "
                        "entityRow realloc!\n");
      fflush(debugOut);
      return -1;
    }
  }

  EntityMeta *tempEnt =
      realloc(table->entitiesMeta, sizeof(EntityMeta) * newCapacity);

  if (tempEnt == NULL)
  {
    fprintf(debugOut, "(IncreaseEntityTableCapacity) NULL pointer from "
                      "entitiesMeta realloc!\n");
    fflush(debugOut);
    return -1;
  }

  for (int i = 0; i < compCount; i++)
  {
    table->componentsColumn[i].entityRow = tempCol[i];
  }
  // table->entitiesCapacity = newCapacity;
  table->entitiesMeta = tempEnt;
  return 1;
}

ComponentColumn *GetComponentColumn(EntitiesData *data, EntityMeta *entity,
                                    uint16_t componentMask)
{
  EntityTable *table = GetArchetypeTable(data, entity->archetypeMask);
  if (!EntityHasComponent(entity, componentMask))
  {
    fprintf(debugOut, "(GetComponentRow) Entity does not have component!\n");
    fflush(debugOut);
    return NULL;
  }
  if (table != NULL)
  {
    int compCount = table->componentsAmount;
    for (int i = 0; i < compCount; i++)
    {
      // fprintf(debugOut, "(GetComponentRow) comp check i: %d\n", i);
      // fflush(debugOut);
      if (table->componentsColumn[i].componentMask == componentMask)
      {
        return &table->componentsColumn[i];
      }
    }
  }
  fprintf(debugOut, "(GetComponentRow) Archetype does not exist!\n");
  fflush(debugOut);
  return NULL;
}

EntityTable *GetArchetypeTable(EntitiesData *data, uint16_t archetypeMask)
{
  if (ArchetypeExists(data, archetypeMask))
  {
    return data->tablePointers[archetypeMask];
  }
  fprintf(debugOut,
          "(GetArchetypeTable) Trying to get table that does not exist!\n");
  fflush(debugOut);
  return NULL;
}

bool EntityHasComponent(EntityMeta *entity, uint16_t componentMask)
{
  return (entity->archetypeMask & componentMask);
}

void InitializeEntitiesData(EntitiesData *entities)
{
  entities->tablePointers = calloc(sizeof(uint16_t), sizeof(EntityTable *));
  entities->tablesCapacity = 256;
  entities->tablesCount = 0;
  entities->tables = malloc(entities->tablesCapacity * sizeof(EntityTable));
}

bool ArchetypeExists(EntitiesData *entities, uint16_t archetypeMask)
{
  if (entities->tablePointers[archetypeMask] != NULL)
  {
    return true;
  }
  return false;
}

int MakeArchetype(EntitiesData *entities, uint16_t archetypeMask)
{
  if (entities->tablesCount == entities->tablesCapacity)
  {
    if (entities->tablesCapacity < sizeof(uint16_t))
    {
      uint16_t increaseBy = 256;
      if (!IncreaseArchetypeTablesSize(entities, increaseBy))
      {
        return -1;
      }
    }
    else
    {
      fprintf(debugOut, "(MakeArchetype) Maximum ammount of tables reached!\n");
      fflush(debugOut);
      return -1;
    }
  }

  int index = entities->tablesCount;

  SetArchetypeTable(&entities->tables[index], archetypeMask);

  entities->tablePointers[archetypeMask] = &entities->tables[index];
  entities->tablesCount++;
  // fprintf(debugOut, "(MakeArchetype) Made new archetype\n");
  // fflush(debugOut);

  return 1;
}

void SetArchetypeTable(EntityTable *table, uint16_t archetypeMask)
{
  table->archetypeMask = archetypeMask;
  table->componentsAmount = 0;
  table->entitiesCount = 0;
  table->entitiesCapacity = 256;
  table->componentsColumn = calloc(16, sizeof(ComponentColumn));
  table->entitiesMeta = malloc(sizeof(EntityMeta) * table->entitiesCapacity);

  for (int i = 0; i < 16; i++)
  {
    uint16_t componentMask = (1 << i);
    if (archetypeMask & componentMask)
    {
      ComponentColumn column;

      switch (componentMask)
      {
      case STRENGTH_MASK:
        column.typeSize = sizeof(Strength);
        column.typeAlignment = _Alignof(Strength);
        break;
      case AGILITY_MASK:
        column.typeSize = sizeof(Agility);
        column.typeAlignment = _Alignof(Agility);
        break;
      case POSITION_MASK:
        column.typeSize = sizeof(Position);
        column.typeAlignment = _Alignof(Position);
        break;
      case SIZE_MASK:
        column.typeSize = sizeof(Size);
        column.typeAlignment = _Alignof(Size);
        break;
      case HEALTH_MASK:
        column.typeSize = sizeof(Health);
        column.typeAlignment = _Alignof(Health);
        break;
      case WEIGHT_MASK:
        column.typeSize = sizeof(Weight);
        column.typeAlignment = _Alignof(Weight);
        break;
      case SYMBOL_MASK:
        column.typeSize = sizeof(Symbol);
        column.typeAlignment = _Alignof(Symbol);
        break;
      default:
        fprintf(
            debugOut,
            "(SetArchetypeTable) No corresponding component type in switch!\n");
        fflush(debugOut);
        continue;
      }
      column.entityRow = calloc(table->entitiesCapacity, column.typeSize);
      if (column.entityRow == NULL)
      {
        fprintf(debugOut,
                "(SetArchetypeTable) Entity row allocation returning null!\n");
        fflush(debugOut);
      }

      column.componentMask = componentMask;
      column.columnIndex = table->componentsAmount;
      table->componentsColumn[column.columnIndex] = column;
      table->componentsAmount++;
      // fprintf(debugOut, "component added to archetype\n");
      // fflush(debugOut);
    }
  }
}

/**
 * Increases the maximum amount of archetype tables in EntitiesData
 */
int IncreaseArchetypeTablesSize(EntitiesData *entities, uint16_t increaseBy)
{
  uint16_t newTablesCap = entities->tablesCapacity + increaseBy;
  EntityTable *temp =
      realloc(entities->tables, sizeof(EntityTable) * newTablesCap);

  if (temp != NULL)
  {
    entities->tables = temp;
    entities->tablesCapacity = newTablesCap;
    return 1;
  }

  fprintf(debugOut,
          "(IncreaseArchetypeTablesSize) realloc of tables pointer failed!\n");
  fflush(debugOut);
  return -1;
}
