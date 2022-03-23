#ifndef _LINKED_LIST_INCLUDED
#define _LINKED_LIST_INCLUDED

typedef struct {
  int year, chassi;
} VEHICLE;

typedef struct Node {
  VEHICLE *vehicle;
  struct Node *next;
} NODE;

typedef struct {
  NODE *head;
  int size;
} LIST;

LIST *create_list();
void prepend_to_list(LIST *list, VEHICLE *v);
void show_list(LIST *list);
void free_list(LIST *list);
VEHICLE *search_chassi(LIST *list, int chassi);

#endif  // _LINKED_LIST_INCLUDED
