#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "queue.h"


typedef struct linkednode {
  void *value;
  struct linkednode *next;
} LinkedNode;


struct Queue {
  LinkedNode *head;
  LinkedNode *tail;
  size_t count;
  size_t esize;
};


Queue* queue_malloc(size_t size) {
  if (!size)
    return NULL;
  Queue *queue = malloc(sizeof(Queue));
  if (!queue)
    return NULL;
  *queue = (Queue){NULL, NULL, 0, size};
  return queue;
}
void queue_free(Queue *queue) {
  if (!queue)
    return;
  LinkedNode *node;
  while (queue->head) {
    free(queue->head->value);
    node = queue->head;
    queue->head = node->next;
    free(node);
  }
  free(queue);
}

size_t queue_count(const Queue *queue) { return (queue ? queue->count : 0); }
size_t queue_esize(const Queue *queue) { return (queue ? queue->esize : 0); }

int queue_enqueue(Queue *queue, const void *value)
{
  if (!queue) return 1;
  // create a new node
  LinkedNode *node = malloc(sizeof(LinkedNode));
  if (!node)
    return 1;
  // copy the value into the new node
  node->value = malloc(queue->esize);
  if (!node->value) {
    free(node);
    return 1;
  }
  memcpy(node->value, value, queue->esize);
  // mark the node as isolated
  node->next = NULL;
  if (!(queue->head)) { // if empty
    queue->head = node;
    queue->tail = queue->head;
  } else { // if not empty
    queue->tail->next = node;
    queue->tail = node;
  }
  queue->count++;
  return 0;
}

int queue_peek(const Queue *queue, void *value)
{
  if (!queue || (!(queue->head)))
    return 1;
  // copy the value to the output value (if applicable)
  if (value)
    memcpy(value, queue->head->value, queue->esize);
  return 0;
}

int queue_dequeue(Queue *queue, void *value)
{
  if (!queue || (!(queue->head)))
    return 1;
  // copy the value to the output value (if applicable)
  if (value)
    memcpy(value, queue->head->value, queue->esize);
  free(queue->head->value);
  if (queue->head == queue->tail) { // if one entry
    free(queue->head);
    queue->head = queue->tail = NULL;
  } else {
    LinkedNode *node = queue->head;
    queue->head = queue->head->next;
    free(node);
  }
  queue->count--;
  return 0;
}
