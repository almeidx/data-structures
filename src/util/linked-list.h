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
void prepend_to_list(LIST *l, VEHICLE *v);
void show_list(LIST *l);
void free_list(LIST *l);
VEHICLE *search_chassi(LIST *l, int chassi);

#endif  // _LINKED_LIST_INCLUDED
