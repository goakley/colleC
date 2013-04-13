#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "stack.h"


typedef struct linkednode {
  void *value;
  struct linkednode *next;
} LinkedNode;


struct Stack {
  LinkedNode *top;
  size_t count;
  size_t esize;
};


Stack* stack_malloc(size_t size) {
  if (!size)
    return NULL;
  Stack *stack = malloc(sizeof(Stack));
  if (!stack)
    return NULL;
  *stack = (Stack){NULL, 0, size};
  return stack;
}
void stack_free(Stack *stack) {
  if (!stack)
    return;
  LinkedNode *node;
  while (stack->top) {
    node = stack->top;
    stack->top = node->next;
    free(node);
  }
  free(stack);
}

size_t stack_count(const Stack *stack) { return (stack ? stack->count : 0); }
size_t stack_esize(const Stack *stack) { return (stack ? stack->esize : 0); }

int stack_push(Stack *stack, const void *value)
{
  if (!stack) return 1;
  // create a new node
  LinkedNode *node = malloc(sizeof(LinkedNode));
  if (!node)
    return 1;
  // copy the value into the new node
  node->value = malloc(stack->esize);
  if (!node->value) {
    free(node);
    return 1;
  }
  memcpy(node->value, value, stack->esize);
  // add the node to the stack
  node->next = stack->top;
  stack->top = node;
  stack->count++;
  return 0;
}

int stack_peek(const Stack *stack, void *value)
{
  if (!stack || (!(stack->top)))
    return 1;
  // copy the value to the output value (if applicable)
  if (value)
    memcpy(value, stack->top->value, stack->esize);
  return 0;
}

int stack_pop(Stack *stack, void *value)
{
  if (!stack || (!(stack->top)))
    return 1;
  // copy the value to the output value (if applicable)
  if (value)
    memcpy(value, stack->top->value, stack->esize);
  free(stack->top->value);
  LinkedNode *node = stack->top;
  stack->top = node->next;
  free(node);
  stack->count--;
  return 0;
}
