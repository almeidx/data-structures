#include "../util/util.c"
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
void prepend_to_list(LIST *list, NODE *node) {
  if (!list || !node) return;
  node->next = list->head;
  list->head = node;
  list->size++;
}

// 9.
void append_to_list(LIST *list, NODE *node) {
  NODE *current = list->head;
  if (!current) {
    prepend_to_list(list, node);
    return;
  }
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = node;
  list->size++;
}

// 10. & 11.
int compare_nodes(NODE *a, NODE *b) {
  return strcmp(a->word->text, b->word->text);
}

// 12.
void add_node_sorted(LIST *list, NODE *node) {
  int _continue = 1;
  NODE *previous, *current;

  if (!list->head) {
    node->next = NULL;
    list->head = node;
  } else {
    previous = current = list->head;

    while (_continue) {
      if (!current || compare_nodes(current, node) > 0) {
        _continue = 0;
      } else {
        previous = current;
        current = current->next;
      }

      if (!_continue) {
        node->next = list->head;
        list->head = node;
      } else {
        previous->next = node;
        node->next = current;
      }
    }
  }

  list->size++;
}

// 13.
NODE *iterative_search(LIST *list, NODE *node) {
  NODE *current = list->head;
  while (current != NULL) {
    if (compare_nodes(current, node)) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

// 14.
NODE *recursive_search(LIST *list, NODE *node, NODE *current) {
  if (current == NULL) {
    return NULL;
  }
  if (compare_nodes(current, node)) {
    return current;
  }
  return recursive_search(list, node, current->next);
}

// 15.
int amount_of_repeated_words(LIST *list) {
  NODE *current = list->head, *tmp;
  int count = 0, discarded_same_node;

  while (current != NULL) {
    discarded_same_node = 0;

    tmp = list->head;

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
int remove_word(LIST *list, char *text) {
  NODE *current = list->head, *previous = NULL;

  while (current) {
    if (strcmp(current->word->text, text) == 0) {
      if (!previous) {
        list->head = current->next;
      } else {
        previous->next = current->next;
      }

      free_node(current);

      list->size--;

      return 1;
    }

    previous = current;
    current = current->next;
  }

  return 0;
}

// 18.
int remove_first_node(LIST *list) {
  if (!list->head) return 0;

  NODE *node = list->head;
  list->head = node->next;

  free_node(node);

  list->size--;
  return 1;
}

// 19.
int remove_last_node(LIST *list) {
  if (!list->head) return 0;

  NODE *current = list->head;
  NODE *previous = NULL;

  while (current->next) {
    previous = current;
    current = current->next;
  }

  if (!previous) {
    list->head = NULL;
  } else {
    previous->next = NULL;
  }

  free_node(current);

  list->size--;
  return 1;
}

// 20.
void print_word(WORD *word) {
  if (!word) return;
  printf("%s\n", word->text);
}

// 21.
void print_list(LIST *list) {
  NODE *current = list->head;

  printf("Language: %s\n", list->language);
  printf("Size: %d\n", list->size);

  while (current != NULL) {
    print_word(current->word);
    current = current->next;
  }
}

// 22.
void print_list_reversed_recursive(LIST *list, NODE *current) {
  if (current == NULL) {
    return;
  }

  print_list_reversed_recursive(list, current->next);
  print_word(current->word);
}

NODE *get_previous_node(LIST *list, NODE *node) {
  NODE *current = list->head;

  while (current != NULL) {
    if (current->next == node) {
      return current;
    }

    current = current->next;
  }

  return NULL;
}

// 23.
void print_list_reversed(LIST *list) {
  if (!list->size) return;

  NODE *current = list->head, *prev;

  // get last node
  while (current->next) {
    current = current->next;
  }

  do {
    print_word(current->word);
    current = get_previous_node(list, current);
  } while (current);
}

// 24.
void free_list(LIST *list) {
  NODE *current = list->head;
  while (current != NULL) {
    NODE *next = current->next;
    free(current->word);
    free(current);
    current = next;
  }
  free(list);
}

// 25.
int export_list_to_file(LIST *list, char *filename) {
  FILE *f = fopen(filename, "w");
  if (!f) return 0;

  NODE *current = list->head;
  while (current) {
    fprintf(f, "%s\n", current->word->text);
    current = current->next;
  }

  fclose(f);
  return 1;
}

// 26.
int read_list_from_file(LIST *list, char *filename) {
  FILE *f = fopen(filename, "r");
  if (!f) return 0;

  char buffer[MAX_WORD_LENGTH];
  while (!feof(f)) {
    fscanf(f, "%s", buffer);
    WORD *word = create_word(buffer);
    NODE *node = create_node();
    node->word = word;
    prepend_to_list(list, node);
  }

  fclose(f);
  return 1;
}

NODE *search_word(LIST *list, char *text) {
  NODE *current = list->head;

  while (current) {
    if (!strcmp(current->word->text, text)) {
      return current;
    }

    current = current->next;
  }

  return NULL;
}

void wait_for_continue() {
  flush_stdin();

  printf("\n\nPress ENTER to continue...");
  getchar();
}

// 27.
// Returns 2 if the list has been freed, 1 if the user wants to exit, 0 otherwise
int menu(LIST *list) {
  int option, should_wait_for_continue = 1;

  do {
    flush_stdin();

    printf(
        "(1) Inserir elementos\n"
        "(2) Retirar elementos\n"
        "(3) Mostrar os elementos pela ordem actual\n"
        "(4) Mostrar os elementos pela ordem inversa\n"
        "(5) Mostrar o numero de elementos da lista\n"
        "(6) Pesquisar por um elemento da lista\n"
        "(7) Verificar se existem elementos repetidos na lista\n"
        "(8) Exportar elementos para um ficheiro de texto\n"
        "(9) Importar elementos de um ficheiro de texto\n"
        "(0) SAIR\n");

    scanf("%d", &option);
  } while (option < 0 || option > 9);

  switch (option) {
    case 1: {
      int res;

      do {
        clear_terminal();
        res = add_menu(list);
      } while (res != 1);

      should_wait_for_continue = 0;
      break;
    }

    case 2: {
      int res;

      do {
        clear_terminal();
        res = remove_menu(list);
      } while (res == 0);

      should_wait_for_continue = 0;
      break;
    }

    case 3:
      print_list(list);
      break;

    case 4:
      print_list_reversed(list);
      break;

    case 5:
      printf("O numero de elementos da lista é %d.\n", list->size);
      break;

    case 6: {
      char text[MAX_WORD_LENGTH];
      read_string(text, "Insira a palavra a pesquisar: ");

      if (search_word(list, text)) {
        printf("A palavra '%s' foi encontrada na lista.\n", text);
      } else {
        printf("A palavra '%s' não foi encontrada na lista.\n", text);
      }

      break;
    }

    case 7: {
      int amount = amount_of_repeated_words(list);

      if (amount == 0) {
        printf("Não existem elementos repetidos na lista.\n");
      } else {
        printf("Existem %d elementos repetidos na lista.\n", amount);
      }

      break;
    }

    case 8: {
      char filename[MAX_WORD_LENGTH];
      read_string(filename, "Insira o nome do ficheiro para o qual quer exportar: ");

      if (!export_list_to_file(list, filename)) {
        printf("Ocorreu um erro ao exportar a lista para o ficheiro.\n");
      } else {
        printf("Lista exportada com sucesso para o ficheiro '%s'.\n", filename);
      }

      break;
    }

    case 9: {
      char filename[MAX_WORD_LENGTH];
      read_string(filename, "Insira o nome do ficheiro de texto do qual quer importar: ");

      if (list->size > 0) {
        free_list(list);
      }

      if (!read_list_from_file(list, filename)) {
        printf("Ocorreu um erro ao importar a lista do ficheiro.\n");
      } else {
        printf("Lista importada com sucesso do ficheiro '%s'.\n", filename);
      }

      break;
    }

    case 0:
      return 1;
  }

  if (should_wait_for_continue) {
    wait_for_continue();
  }

  return 0;
}

// 28.
// Returns 2 if the list has been destroyed, 1 if the user wants to go back, 0 otherwise
int remove_menu(LIST *list) {
  int option;

  do {
    flush_stdin();

    printf(
        "(10) Retirar o primeiro elemento\n"
        "(11) Retirar um elemento\n"
        "(12) Retirar o ultimo elemento\n"
        "(13) Destruir a lista\n"
        "(00) VOLTAR ao menu principal\n");

    scanf("%d", &option);
  } while (option != 0 && (option < 10 || option > 13));

  switch (option) {
    case 10:
      remove_first_node(list);
      break;

    case 11: {
      char text[MAX_WORD_LENGTH];
      read_string(text, "Insira o texto da palavra que deseja remover: ");

      remove_word(list, text);
      break;
    }

    case 12:
      remove_last_node(list);
      break;

    case 13:
      free_list(list);
      return 2;

    case 0:
      return 1;
  }

  return 0;
}

// 29. Returns 1 if the user wants to go back, 0 otherwise
int add_menu(LIST *list) {
  int option;

  do {
    flush_stdin();

    printf(
        "(1) Inserir elemento no inicio\n"
        "(2) Inserir elemento no fim\n"
        "(3) Reordenar lista\n"
        "(0) VOLTAR ao menu principal\n");

    scanf("%d", &option);
  } while (option < 0 || option > 3);

  switch (option) {
    case 1: {
      char text[MAX_WORD_LENGTH];
      read_string(text, "Insira o texto da palavra que deseja inserir: ");

      NODE *node = create_node();
      node->word = create_word(text);

      prepend_to_list(list, node);

      printf("Palavra '%s' adicionada ao início da lista com sucesso.\n", text);
      break;
    }

    case 2: {
      char text[MAX_WORD_LENGTH];
      read_string(text, "Insira o texto da palavra que deseja inserir: ");

      NODE *node = create_node();
      node->word = create_word(text);

      append_to_list(list, node);

      printf("Palavra '%s' adicionada ao fim da lista com sucesso.\n", text);
      break;
    }

    case 3:
      fast_bubble_sort_list(list);
      break;

    case 0:
      return 1;
  }

  return 0;
}

void swap_nodes(NODE *a, NODE *b) {
  WORD *temp = a->word;
  a->word = b->word;
  b->word = temp;
}

// 30.
void bubble_sort_list(LIST *list) {
  NODE *current;

  if (list->head == NULL) return;

  do {
    current = list->head;

    while (current->next != NULL) {
      if (compare_nodes(current, current->next) > 0) {
        swap_nodes(current, current->next);
      }

      current = current->next;
    }
  } while (current->next != NULL);
}

// 30. "pro"
void fast_bubble_sort_list(LIST *list) {
  int swapped;
  NODE *current;

  if (list->head == NULL) return;

  do {
    swapped = 0;
    current = list->head;

    while (current->next != NULL) {
      if (compare_nodes(current, current->next) > 0) {
        swap_nodes(current, current->next);
        swapped = 1;
      }

      current = current->next;
    }
  } while (swapped);
}
