#ifndef GENERIC_LIST_H_INCLUDED
#define GENERIC_LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
} NODE;

typedef struct List {
  NODE *head;
  int size;
} LIST;

LIST *create_list();

void add_to_list(LIST *list, void *data);
void *remove_from_list(LIST *list, void *data, int (*compare)(void *, void *));

void show_list(LIST *list, void (*show_item)(void *));

void destroy_list(LIST *list, void (*destroy_item)(void *));

void *search_list(LIST *list, void *data, int (*compare)(void *, void *));

#endif  // GENERIC_LIST_H_INCLUDED
