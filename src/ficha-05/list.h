#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/*
  1. Redefina as estruturas Elemento e Lista, de modo a suportar a construção de uma lista de elementos bi-ligada.
*/

#define MAX_WORD_SIZE 51

typedef struct Word {
  char *text;
} WORD;

typedef struct Node {
  WORD *info;
  struct Node *next, *prev;
} NODE;

typedef struct List {
  NODE *head, *tail;
  int size;
} LIST;

LIST *create_list();
NODE *create_node(char *text);
void insert_node_sorted(LIST *list, NODE *node);
NODE *remove_node(LIST *list, NODE *node);
NODE *remove_first_node(LIST *list);
void print_list(LIST *list);
void print_list_inverse(LIST *list);
void print_n_before_node(LIST *list, NODE *node, int n);

void free_node(NODE *node);
void free_list(LIST *list);

NODE *search_node_by_word(LIST *list, char *text);
void remove_word(LIST *list, char *text);

int menu(LIST *list);

#endif  // LIST_H_INCLUDED
