#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "container.h"

/*
  2. Defina uma estrutura de dados adequada para manter em memória RAM uma pilha de contentores.
*/
typedef struct Node {
  CONTAINER *data;
  struct Node *next;
} NODE;

typedef struct Stack {
  NODE *top;
  int size;
} STACK;

STACK *create_stack();
void push_to_stack(STACK *stack, CONTAINER *data);
CONTAINER *pop_stack(STACK *stack);
CONTAINER *top_of_stack(STACK *stack);
int get_stack_size(STACK *stack);

void show_stack(STACK *stack, void (*show_container)(CONTAINER *));
void destroy_stack(STACK *stack);

int menu(STACK *stack);

#endif  // STACK_H_INCLUDED
