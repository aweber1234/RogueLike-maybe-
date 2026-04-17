#include <stdlib.h>
#include "functions.h"

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
