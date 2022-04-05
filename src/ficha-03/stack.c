#ifndef NULL
#include <stdio.h>
#endif  // NULL

#include "stack.h"

STACK *create_stack() {
  STACK *s = (STACK *)malloc(sizeof(STACK));
  s->inicio = NULL;
  s->size = 0;
  return s;
}

void push_to_stack(STACK *stack, CONTAINER *data) {
  NODE *new_node = (NODE *)malloc(sizeof(NODE));
  new_node->data = data;
  new_node->next = stack->inicio;
  stack->inicio = new_node;
  stack->size++;
}

CONTAINER *pop_stack(STACK *stack) {
  if (!stack || !stack->size) return NULL;

  CONTAINER *data = stack->inicio->data;
  NODE *aux = stack->inicio;
  stack->inicio = stack->inicio->next;
  free(aux);
  stack->size--;
  return data;
}

CONTAINER *top_of_stack(STACK *stack) {
  if (!stack || !stack->size) return NULL;
  return stack->inicio->data;
}

void show_stack(STACK *stack, void (*show_container)(CONTAINER *)) {
  if (!stack || !stack->size) return;

  NODE *aux = stack->inicio;

  printf("------ Stack ------\n");

  while (aux) {
    show_container(aux->data);
    aux = aux->next;
  }
}

void destroy_stack(STACK *stack) {
  if (!stack || !stack->size) return;
  NODE *aux = stack->inicio;
  while (aux) {
    NODE *aux2 = aux->next;
    free(aux);
    aux = aux2;
  }
  free(stack);
}
