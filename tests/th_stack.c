#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"


typedef struct {
  Stack *stack;
} fixture_stack;


void fixture_setup(fixture_stack *fstack, gconstpointer test_data)
{
  fstack->stack = stack_malloc(sizeof(int));
}
void fixture_teardown(fixture_stack *fstack, gconstpointer test_data)
{
  stack_free(fstack->stack);
}

void test_random(fixture_stack *fstack, gconstpointer test_data)
{
  g_assert(stack_esize(fstack->stack) == sizeof(int));
  srand(time(NULL));
  int i;
  for (i = 0; i < 256; i++)
    {
      double random = rand()/(double)RAND_MAX;
      size_t count = stack_count(fstack->stack);
      if (random > 0.61803398875)
	{ // pop data
	  int peek, pop;
	  if (count == 0)
	    {
	      g_assert(stack_peek(fstack->stack, &peek) != 0);
	      g_assert(stack_pop(fstack->stack, &pop) != 0);
	      g_assert(stack_count(fstack->stack) == 0);
	    }
	  else
	    {
	      g_assert(stack_peek(fstack->stack, &peek) == 0);
	      g_assert(stack_pop(fstack->stack, &pop) == 0);
	      g_assert(peek == pop);
	      g_assert(stack_count(fstack->stack) == (count-1));
	    }
	}
      else
	{ // push data
	  g_assert(stack_push(fstack->stack, &i) == 0);
	  g_assert(stack_count(fstack->stack) == (count+1));
	  int peek;
	  g_assert(stack_peek(fstack->stack, &peek) == 0);
	  g_assert(peek == i);
	}
    }
}

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add("/stack/random test", fixture_stack, NULL, 
	     fixture_setup, test_random, fixture_teardown);
  return g_test_run();
}
