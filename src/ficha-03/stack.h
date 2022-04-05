#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "container.h"

typedef struct Node {
  CONTAINER *data;
  struct Node *next;
} NODE;

typedef struct Stack {
  NODE *inicio;
  int size;
} STACK;

STACK *create_stack();
void push_to_stack(STACK *stack, CONTAINER *data);
CONTAINER *pop_stack(STACK *stack);
CONTAINER *top_of_stack(STACK *stack);
void show_stack(STACK *stack, void (*show_container)(CONTAINER *));
void destroy_stack(STACK *stack);

int get_stack_size(STACK *stack) {}

#endif  // STACK_H_INCLUDED
