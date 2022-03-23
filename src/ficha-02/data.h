#ifndef _INCLUDED_DATA_H
#define _INCLUDED_DATA_H

#define MAX_WORD_LENGTH 51

// 1.
typedef struct Word {
  char text[MAX_WORD_LENGTH];
} WORD;

// 2.
typedef struct Node {
  WORD *word;
  struct Node *next;
} NODE;

// 3.
typedef struct List {
  NODE *head;
  int size;
  char language[3];
} LIST;

WORD *create_word(char *text);
LIST *create_list(char *language);
NODE *create_node();
int validate_word(char *text);
void prepend_to_list(LIST *l, NODE *node);
void append_to_list(LIST *l, NODE *node);
int compare_nodes(NODE *a, NODE *b);
void add_node_sorted(LIST *l, NODE *node);
NODE *iterative_search(LIST *l, NODE *node);
NODE *recursive_search(LIST *l, NODE *node, NODE *current);
int amount_of_repeated_words(LIST *l);
void free_node(NODE *node);
int remove_word(LIST *l, char *text);
int remove_first_word(LIST *l);
int remove_last_word(LIST *l);
void print_word(WORD *word);
void show_list(LIST *l);
void show_list_reversed_recursive(LIST *l, NODE *current);
void show_list_reversed_iterative(LIST *l);
void free_list(LIST *l);
int export_list_to_file(LIST *l, char *filename);
int read_list_from_file(LIST *l, char *filename);

#endif  // _INCLUDED_DATA_H
