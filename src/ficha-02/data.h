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
void prepend_to_list(LIST *list, NODE *node);
void append_to_list(LIST *list, NODE *node);
int compare_nodes(NODE *a, NODE *b);
void add_node_sorted(LIST *list, NODE *node);
NODE *iterative_search(LIST *list, NODE *node);
NODE *recursive_search(LIST *list, NODE *node, NODE *current);
int amount_of_repeated_words(LIST *list);
void free_node(NODE *node);
int remove_word(LIST *list, char *text);
int remove_first_word(LIST *list);
int remove_last_word(LIST *list);
void print_word(WORD *word);
void show_list(LIST *list);
void show_list_reversed_recursive(LIST *list, NODE *current);
void show_list_reversed_iterative(LIST *list);
void free_list(LIST *list);
int export_list_to_file(LIST *list, char *filename);
int read_list_from_file(LIST *list, char *filename);

NODE *search_word(LIST *list, char *text);
int menu(LIST *list);
int menu_to_remove(LIST *list);

#endif  // _INCLUDED_DATA_H
