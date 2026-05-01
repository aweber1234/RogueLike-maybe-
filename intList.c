#include "sharedData.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "typeDefinitions.h"



IntList IntListConstruct()
{
  IntList list;
  list.arrayLocation = malloc(sizeof(int) * 256);
  list.count = 0;
  return list;
}

int IntListResize(IntList *list, int newSize)
{
  if (newSize > 0)
  {
    if (newSize >= list->count)
    {
      int tempArray[list->count];
      for (int i = 0; i < list->count; i++)
      {
        tempArray[i] = list->arrayLocation[i];
      }

      list->arrayLocation = realloc(list->arrayLocation, sizeof(int) * newSize);

      for (int i = 0; i < list->count; i++)
      {
        list->arrayLocation[i] = tempArray[i];
      }
    }
    else
    {
      fprintf(debugOut, "Size must fit the amount of items in list!\n");
      return -1;
    }
  }
  else
  {
    fprintf(debugOut, "Size for list must be positive!\n");
    return -1;
  }
  return 1;
}

void IntListAdd(IntList *list, int item)
{
  if (list->count % 256 == 0)
  {
    int newSize = list->count + 256;

    if (IntListResize(list, newSize) < 0)
    {
      return;
    }
  }

  list->arrayLocation[list->count] = item;
  list->count++;
}

void IntListRemove(IntList *list, int itemIndex)
{
  if (itemIndex < list->count && itemIndex > -1)
  {
    int tempArray[list->count];
    for (int i = itemIndex + 1; i < list->count; i++)
    {
      tempArray[i] = list->arrayLocation[i];
    }

    for (int i = itemIndex; i < list->count - 1; i++)
    {
      list->arrayLocation[i] = tempArray[i + 1];
    }

    list->count--;
  }
  else
  {
    fprintf(debugOut, "Item index does not exist!\n");
  }
}
