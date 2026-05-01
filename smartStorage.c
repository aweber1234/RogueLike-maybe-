#include "functions.h"
#include "typeDefinitions.h"
#include <stdio.h>
#include <stdlib.h>

void SmartStorageInitialize(SmartStorage *data, int storageTypeSize)
{
  data->typeSize = storageTypeSize;
  data->highestItemIndex = -1;
  data->freeSpots = IntListConstruct();
}

int SmartStorageNextIndex(SmartStorage *data)
{
  size_t size = data->typeSize;
  int newIndex;

  // if there are free spots use them
  if (data->freeSpots.count > 0)
  {
    newIndex = data->freeSpots.arrayLocation[data->freeSpots.count];
    IntListRemove(&data->freeSpots, data->freeSpots.count);
  }
  // just use the next incremented index
  else
  {
    data->highestItemIndex++;
    newIndex = data->highestItemIndex;
  }
  return newIndex;
}

void SmartStorageRemoveAt(SmartStorage *data, int index)
{
  if (index < data->highestItemIndex)
  {
    IntListAdd(&data->freeSpots, index);
  }
  else if (index == data->highestItemIndex)
  {
    data->highestItemIndex--;
  }
}
