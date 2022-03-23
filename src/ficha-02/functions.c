#include "data.h"
#include "words.c"

// 4.
LIST *create_list(char *language) {
  LIST *list = (LIST *)malloc(sizeof(LIST));
  list->head = NULL;
  list->size = 0;

  if (strlen(language) == 2) {
    strcpy(list->language, language);
  } else {
    printf("create_list(): Language must be 2 characters long.\n");
    strcpy(list->language, "??");
  }

  return list;
}

// 5.
NODE *create_node() {
  NODE *node = (NODE *)malloc(sizeof(NODE));
  node->word = NULL;
  node->next = NULL;
  return node;
}

int is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// 6.
int validate_word(char *text) {
  size_t len = strlen(text);

  if (len > MAX_WORD_LENGTH) {
    return 0;
  }

  for (int i = 0; i < len; i++) {
    if (!is_alpha(text[i])) {
      return 0;
    }
  }

  return 1;
}

// 8.
void prepend_to_list(LIST *l, NODE *node) {
  if (!l || !node) return;
  node->next = l->head;
  l->head = node;
  l->size++;
}

// 9.
void append_to_list(LIST *l, NODE *node) {
  NODE *current = l->head;
  if (!current) {
    prepend_to_list(l, node);
    return;
  }
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = node;
  l->size++;
}

// 10, 11
int compare_nodes(NODE *a, NODE *b) {
  return !strcmp(a->word->text, b->word->text);
}

// 12.
void add_node_sorted(LIST *l, NODE *node) {}

// 13.
NODE *iterative_search(LIST *l, NODE *node) {
  NODE *current = l->head;
  while (current != NULL) {
    if (compare_nodes(current, node)) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

// 14.
NODE *recursive_search(LIST *l, NODE *node, NODE *current) {
  if (current == NULL) {
    return NULL;
  }
  if (compare_nodes(current, node)) {
    return current;
  }
  return recursive_search(l, node, current->next);
}

// 15.
int amount_of_repeated_words(LIST *l) {
  NODE *current = l->head, *tmp;
  int count = 0, discarded_same_node;

  while (current != NULL) {
    discarded_same_node = 0;

    tmp = l->head;

    while (tmp != NULL) {
      if (compare_nodes(current, tmp)) {
        if (!discarded_same_node) {
          discarded_same_node = 1;
        } else {
          count++;
        }
      }

      tmp = tmp->next;
    }

    current = current->next;
  }

  return count;
}

// 16.
void free_node(NODE *node) {
  if (node == NULL) return;
  free(node->word);
  free(node);
}

// 17.
int remove_word(LIST *l, char *text) {
  NODE *current = l->head;
  NODE *previous = NULL;

  while (current) {
    if (strcmp(current->word->text, text) == 0) {
      if (!previous) {
        l->head = current->next;
      } else {
        previous->next = current->next;
      }

      free_node(current);

      l->size--;

      return 1;
    }
    previous = current;
    current = current->next;
  }

  return 0;
}

// 18.
int remove_first_word(LIST *l) {
  if (!l->head) return 0;

  NODE *node = l->head;
  l->head = node->next;

  free_node(node);

  l->size--;
  return 1;
}

// 19.
int remove_last_word(LIST *l) {
  if (!l->head) return 0;

  NODE *current = l->head;
  NODE *previous = NULL;

  while (current->next) {
    previous = current;
    current = current->next;
  }

  if (!previous) {
    l->head = NULL;
  } else {
    previous->next = NULL;
  }

  free_node(current);

  l->size--;
  return 1;
}

// 20.
void print_word(WORD *word) {
  if (!word) return;
  printf("%s\n", word->text);
}

// 21.
void show_list(LIST *l) {
  NODE *current = l->head;

  printf("Language: %s\n", l->language);
  printf("Size: %d\n", l->size);

  while (current != NULL) {
    print_word(current->word);
    current = current->next;
  }
}

// 22.
void show_list_reversed_recursive(LIST *l, NODE *current) {
  if (current == NULL) {
    return;
  }
  show_list_reversed_recursive(l, current->next);
  print_word(current->word);
}

// 23.
void show_list_reversed_iterative(LIST *l) {
  NODE *current = l->head;
  NODE *previous = NULL;

  while (current != NULL) {
    NODE *next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  l->head = previous;

  show_list(l);
}

// 24.
void free_list(LIST *l) {
  NODE *current = l->head;
  while (current != NULL) {
    NODE *next = current->next;
    free(current->word);
    free(current);
    current = next;
  }
  free(l);
}

// 25.
int export_list_to_file(LIST *l, char *filename) {
  FILE *f = fopen(filename, "w");
  if (!f) return 0;

  NODE *current = l->head;
  while (current) {
    fprintf(f, "%s\n", current->word->text);
    current = current->next;
  }

  fclose(f);
  return 1;
}

// 26.
int read_list_from_file(LIST *l, char *filename) {
  FILE *f = fopen(filename, "r");
  if (!f) return 0;

  char buffer[MAX_WORD_LENGTH];
  while (!feof(f)) {
    fscanf(f, "%s", buffer);
    WORD *word = create_word(buffer);
    NODE *node = create_node();
    node->word = word;
    prepend_to_list(l, node);
  }

  fclose(f);
  return 1;
}

// 27.
char menu() {
  int option;

  do {
    printf(
        "(1) Inserir um novo elemento na lista"
        "(2) Retirar elementos da lista ( ir para o sub menu)"
        "(3) Mostrar os elementos pela ordem actual"
        "(4) Mostrar os elementos pela ordem inversa"
        "(5) Mostrar o numero de elementos da lista"
        "(6) Pesquisar por um elemento da lista"
        "(7) Verificar se existem elementos repetidos na lista"
        "(8) Exportar elementos para um ficheiro de texto"
        "(9) Importar elementos de um ficheiro de texto"
        "(0) SAIR");

    scanf("%d", &option);
  } while (option < 0 || option > 9);

  // TODO
  switch (option) {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    case 0:
      break;
  }
}

// 28.
void menu_to_remove() {
  int option;

  do {
    printf(
        "(10) Retirar o primeiro elemento"
        "(11) Retirar um elemento especificado pelo utilizador"
        "(12) Retirar o último elemento"
        "(13) Destruir a lista de elementos"
        "( 0) VOLTAR ao Menu Principal");

    scanf("%d", &option);
  } while (option != 0 || (option < 10 && option > 13));

  // TODO
  switch (option) {
    case 10:
      break;
    case 11:
      break;
    case 12:
      break;
    case 13:
      break;
    case 0:
      break;
  }
}
