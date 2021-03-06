#include "generic-list.h"

LIST *create_list() {
  LIST *list = (LIST *)malloc(sizeof(LIST));
  if (!list) return NULL;

  list->head = NULL;
  list->size = 0;
  return list;
}

void add_to_list(LIST *list, void *data) {
  if (!list) return;

  NODE *node = (NODE *)malloc(sizeof(NODE));
  if (!node) return;

  node->data = data;
  node->next = NULL;

  if (!list->head) {
    list->head = node;
  } else {
    NODE *current = list->head;
    while (current->next) {
      current = current->next;
    }
    current->next = node;
  }

  list->size++;
}

void *remove_from_list(LIST *list, void *data, int (*compare)(void *, void *)) {
  if (!list) return;

  NODE *current = list->head, *previous = NULL;

  while (current) {
    if (compare(current->data, data)) {
      if (previous) {
        previous->next = current->next;
      } else {
        list->head = current->next;
      }

      list->size--;

      void *data = current->data;
      free(current);

      return data;
    }

    previous = current;
    current = current->next;
  }

  return NULL;
}

void show_list(LIST *list, void (*show_item)(void *)) {
  if (!list) return;

  NODE *current = list->head;
  while (current) {
    show_item(current->data);
    current = current->next;
  }

  printf("\n");
}

void destroy_list(LIST *list, void (*destroy_item)(void *)) {
  if (!list) return;

  NODE *current = list->head, *next;
  while (current) {
    next = current->next;

    destroy_item(current->data);
    free(current);

    current = next;
  }

  free(list);
}

void *search_list(LIST *list, void *data, int (*compare)(void *, void *)) {
  if (!list) return NULL;

  NODE *current = list->head;
  while (current) {
    if (compare(current->data, data)) {
      return current->data;
    }
    current = current->next;
  }

  return NULL;
}
