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

void prepend_to_list(LIST *list, VEHICLE *v) {
  NODE *new_node = (NODE *)malloc(sizeof(NODE));
  new_node->vehicle = v;
  new_node->next = list->head;
  list->head = new_node;
  list->size++;
}

extern void print_vehicle(VEHICLE *v);
void show_list(LIST *list) {
  NODE *current = list->head;
  while (current) {
    print_vehicle(current->vehicle);
    current = current->next;
  }
}

void show_list_func_arg(LIST *list, void(show_vehicle)(VEHICLE *)) {
  NODE *current = list->head;
  while (current) {
    show_vehicle(current->vehicle);
    current = current->next;
  }
}

void free_list(LIST *list) {
  NODE *current = list->head;
  while (current) {
    NODE *next = current->next;
    free(current->vehicle);
    free(current);
    current = next;
  }
  free(list);
}

VEHICLE *search_chassi(LIST *list, int chassi) {
  NODE *current = list->head;
  while (current) {
    if (current->vehicle->chassi == chassi) {
      return current->vehicle;
    }
    current = current->next;
  }
  return NULL;
}

int remove_vehicle(LIST *list, int chassi) {
  NODE *current = list->head, *previous = NULL;
  int stop = 0;

  while (current && !stop) {
    if (current->vehicle->chassi == chassi) {
      stop = 1;
    } else {
      previous = current;
      current = current->next;
    }
  }

  if (stop) {
    if (previous) {
      previous->next = current->next;
    } else {
      list->head = current->next;
    }

    free(current->vehicle);
    free(current);

    list->size--;

    return 1;
  }

  return 0;
}

int add_sorted(LIST *list, VEHICLE *vehicle) {
  NODE *current = list->head, *previous = NULL;
  int stop = 0;

  while (current && !stop) {
    if (current->vehicle->chassi < vehicle->chassi) {
      previous = current;
      current = current->next;
    } else {
      stop = 1;
    }
  }

  NODE *new_node = (NODE *)malloc(sizeof(NODE));
  new_node->vehicle = vehicle;
  new_node->next = NULL;

  if (previous) {
    previous->next = new_node;
  } else {  // list is empty
    list->head = new_node;
  }

  if (current) {  // if there are more nodes after
    new_node->next = current;
  }

  list->size++;

  return 1;
}
