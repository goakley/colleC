#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "bivector.h"


struct Bivector {
  unsigned char *array;
  size_t count;
};


Bivector* bivector_malloc(size_t count, unsigned char set)
{
  if (!count)
    return NULL;
  Bivector *biv = malloc(sizeof(Bivector));
  if (!biv)
    return NULL;
  biv->count = count;
  biv->array = malloc(count/CHAR_BIT);
  if (!(biv->array)) {
    free(biv);
    return NULL;
  }
  memset(biv->array, (set ? ~(set & 0) : 0), count/CHAR_BIT);
  return biv;
}
void bivector_free(Bivector *biv)
{
  if (!biv)
    return;
  free(biv->array);
  free(biv);
}

int bivector_resize(Bivector *biv, size_t count, unsigned char set)
{
  if (!biv || !count)
    return 1;
  unsigned char *array = malloc(count/CHAR_BIT);
  if (!array)
    return 1;
  if (count > biv->count)
    { // INCREASE the size
      memset(array, 0, count/CHAR_BIT);
      memcpy(array, biv->array, (biv->count)/CHAR_BIT);
    }
  else
    { // DECREASE the size
      memcpy(array, biv->array, count/CHAR_BIT);
      //
      //
      // FIX FIX FIX FIX FIX FIX FIX (USING SET TOO)
      //
      //
    }
  free(biv->array);
  biv->array = array;
  biv->count = count;
  return 0;
}

/** \todo Efficiency of algorithm */
void bivector_set(Bivector *biv, size_t min, size_t max)
{
  if (!biv)
    return;
  size_t index;
  for (index = min; index <= max; index++)
    (biv->array)[index/CHAR_BIT] |= (1 << (index%CHAR_BIT));
}

/** \todo Efficiency of algorithm */
void bivector_clear(Bivector *biv, size_t min, size_t max)
{
  if (!biv)
    return;
  size_t index;
  for (index = min; index <= max; index++)
    (biv->array)[index/CHAR_BIT] &= ~(1 << (index%CHAR_BIT));
}

/** \todo Efficiency of algorithm */
void bivector_toggle(Bivector *biv, size_t min, size_t max)
{
  if (!biv)
    return;
  size_t index;
  for (index = min; index <= max; index++)
    (biv->array)[index/CHAR_BIT] ^= (1 << (index%CHAR_BIT));
}

/** \todo Efficiency of algorithm */
unsigned char bivector_test(const Bivector *biv, size_t min, size_t max, 
			    unsigned char* result)
{
  if (!biv)
    return 0;
  unsigned char first = 0;
  if (min <= max)
    first = (biv->array)[min/CHAR_BIT] & (1 << (min%CHAR_BIT));
  if (first)
    first = 1;
  if (!result)
    return (first ? 1 : 0);
  size_t index;
  for (index = min; index <= max; index++)
    result[(index-min)/CHAR_BIT] = 
      (biv->array)[index/CHAR_BIT] & (1 << (index%CHAR_BIT));
  return first;
}
