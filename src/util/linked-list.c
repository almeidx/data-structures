#ifndef NULL
#include <stdio.h>
#include <stdlib.h>
#endif

#include "linked-list.h"

LIST *create_list() {
  LIST *list = (LIST *)malloc(sizeof(LIST));
  list->head = NULL;
  list->size = 0;
  return list;
}

void prepend_to_list(LIST *l, VEHICLE *v) {
  NODE *new_node = (NODE *)malloc(sizeof(NODE));
  new_node->vehicle = v;
  new_node->next = l->head;
  l->head = new_node;
  l->size++;
}

extern void print_vehicle(VEHICLE *v);
void show_list(LIST *l) {
  NODE *current = l->head;
  while (current != NULL) {
    print_vehicle(current->vehicle);

    current = current->next;
  }
}

void free_list(LIST *l) {
  NODE *current = l->head;
  while (current != NULL) {
    NODE *next = current->next;
    free(current->vehicle);
    free(current);
    current = next;
  }
  free(l);
}

VEHICLE *search_chassi(LIST *l, int chassi) {
  NODE *current = l->head;
  while (current != NULL) {
    if (current->vehicle->chassi == chassi) {
      return current->vehicle;
    }
    current = current->next;
  }
  return NULL;
}
