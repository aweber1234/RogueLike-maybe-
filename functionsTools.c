#include "functions.h"
#include <stddef.h>
#include <stdlib.h>

int RandRange(int n)
{
  int limit;
  int r;
  n += 1;
  limit = RAND_MAX - (RAND_MAX % n);

  while ((r = rand()) >= limit)
    ;

  return r % n;
}

void *VoidIndexTo(void *start, int index, size_t typeSize)
{
  return (char *)start + (index * typeSize);
}
