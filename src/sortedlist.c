#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "sortedlist.h"

#define INCREASE_CONST 32


struct SortedList {
  void *elements;
  size_t capacity;
  int (*compar)(const void*,const void*);
  size_t count;
  size_t esize;
};


SortedList* sortedlist_malloc(size_t size, 
			      int (*compar)(const void*, const void*))
{
  if (!size || !compar)
    return NULL;
  SortedList *sortedlist = malloc(sizeof(SortedList));
  if (!sortedlist)
    return NULL;
  *sortedlist = (SortedList){NULL,INCREASE_CONST, compar, 0, size};
  sortedlist->elements = malloc(INCREASE_CONST*size);
  if (!(sortedlist->elements)) {
    free(sortedlist);
    return NULL;
  }
  return sortedlist;
}
void sortedlist_free(SortedList *sortedlist)
{
  if (!sortedlist)
    return;
  free(sortedlist->elements);
  free(sortedlist);
}

size_t sortedlist_count(const SortedList *sortedlist)
{ return (sortedlist ? sortedlist->count : 0); }
size_t sortedlist_esize(const SortedList *sortedlist)
{ return (sortedlist ? sortedlist->esize : 0); }

int sortedlist_add(SortedList *sortedlist, const void *value, size_t *index)
{
  if (!sortedlist || !value)
    return 1;
  if ((sortedlist->count) == (sortedlist->capacity))
    { // increase the capacity of the underlying array
      size_t temp_capacity = (sortedlist->capacity)*INCREASE_CONST;
      void *temp_elements = realloc(sortedlist->elements, 
				    temp_capacity*(sortedlist->esize));
      if (!temp_elements)
	return 1;
      sortedlist->elements = temp_elements;
      sortedlist->capacity = temp_capacity;
    }
  size_t imin = 0;
  size_t imax = sortedlist->count;
  size_t imid = 0;
  int comparator = 0;
  while (imin < imax)
    {
      imid = (imin+imax)/2;
      void *element = (sortedlist->elements)+((sortedlist->esize)*imid);
      comparator = (sortedlist->compar)(value, element);
      if (comparator < 0) // key is less than element
	imax = imid;
      else if (comparator > 0) // key is greater than element
	imin = imid + 1;
      else
	break;
    }
  if (comparator > 0)
    imid++;
  memmove(sortedlist+(sortedlist->esize)*(imid+1), 
	  sortedlist+(sortedlist->esize)*imid,
	  (sortedlist->esize)*((sortedlist->count)-imid));
  memcpy((sortedlist->elements)+(sortedlist->esize)*imid, value,
	 sortedlist->esize);
  sortedlist->count++;
  if (index)
    *index = imid;
  return 0;
}

int sortedlist_find(const SortedList *sortedlist, const void *key,
		    void *value, size_t *index)
{
  if (!sortedlist || !key || (!value && !index))
    return 1;
  size_t imin = 0;
  size_t imax = sortedlist->count;
  size_t imid;
  while (imin < imax)
    {
      imid = (imax+imin)/2;
      void *element = (sortedlist->elements)+((sortedlist->esize)*imid);
      int comparator = (sortedlist->compar)(key, element);
      if (comparator < 0) // key is less than element
	imax = imid;
      else if (comparator > 0) // key is greater than element
	imin = imid + 1;
      else
	{
	  if (value) memcpy(value, element, sortedlist->esize);
	  if (index) *index = imid;
	  return 0;
	}
    }
  return 1;
}

int sortedlist_element(const SortedList *sortedlist, size_t index, 
		       void *value)
{
  if (!sortedlist || (index >= (sortedlist->count)))
    return 1;
  if (value)
    memcpy(value, (sortedlist->elements)+((sortedlist->esize)*index), 
	   sortedlist->esize);
  return 0;
}

int sortedlist_remove(SortedList *sortedlist, size_t index, void *value)
{
  if (!sortedlist || (index >= (sortedlist->count)))
    return 1;
  if (value)
    sortedlist_element(sortedlist, index, value);
  sortedlist->count--;
  memmove((sortedlist->elements)+(sortedlist->esize)*index, 
	  (sortedlist->elements)+(sortedlist->esize)*(index+1),
	  (sortedlist->esize)*((sortedlist->count)-index));
  return 0;
}
