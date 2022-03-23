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

// 10, 11
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
int remove_first_word(LIST *list) {
  if (!list->head) return 0;

  NODE *node = list->head;
  list->head = node->next;

  free_node(node);

  list->size--;
  return 1;
}

// 19.
int remove_last_word(LIST *list) {
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
void show_list(LIST *list) {
  NODE *current = list->head;

  printf("Language: %s\n", list->language);
  printf("Size: %d\n", list->size);

  while (current != NULL) {
    print_word(current->word);
    current = current->next;
  }
}

// 22.
void show_list_reversed_recursive(LIST *list, NODE *current) {
  if (current == NULL) {
    return;
  }
  show_list_reversed_recursive(list, current->next);
  print_word(current->word);
}

// 23.
void show_list_reversed_iterative(LIST *list) {
  NODE *current = list->head;
  NODE *previous = NULL;

  while (current != NULL) {
    NODE *next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  list->head = previous;

  show_list(list);
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

// 27.
// Returns 2 if the list has been freed, 1 if the user wants to leave, 0 otherwise
int menu(LIST *list) {
  clear_terminal();

  int option;

  do {
    printf(
        "(1) Inserir um novo elemento na lista\n"
        "(2) Retirar elementos da lista (ir para o sub menu)\n"
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
      char text[MAX_WORD_LENGTH];
      read_string(text, "Insira a nova palavra: ");

      NODE *node = create_node();
      node->word = create_word(text);

      int pos;

      do {
        pos = read_int("Deseja inserir o elemento ao inicio (0) ou ao fim (1): ");
      } while (pos != 0 && pos != 1);

      if (pos) {
        append_to_list(list, node);
      } else {
        prepend_to_list(list, node);
      }

      printf("Palavra '%s' adicionada à lista com sucesso.\n", text);
      break;
    }

    case 2:
      if (menu_to_remove(list)) {
        return 2;
      }
      break;

    case 3:
      show_list(list);
      break;

    case 4:
      show_list_reversed_iterative(list);
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

  return 0;
}

// 28.
// Returns 2 if the list has been freed, 1 if a single element was removed, 0 otherwise
int menu_to_remove(LIST *list) {
  int option;

  do {
    printf(
        "(10) Retirar o primeiro elemento"
        "(11) Retirar um elemento especificado pelo utilizador"
        "(12) Retirar o último elemento"
        "(13) Destruir a lista de elementos"
        "(00) VOLTAR ao Menu Principal");

    scanf("%d", &option);
  } while (option != 0 && (option < 10 || option > 13));

  switch (option) {
    case 10:
      return remove_first_word(list);

    case 11: {
      char text[MAX_WORD_LENGTH];
      read_string(text, "Insira o texto da palavra que deseja remover: ");

      return remove_word(list, text);
    }

    case 12:
      return remove_last_word(list);

    case 13:
      free_list(list);
      return 1;

    case 0:
      break;
  }

  return 0;
}
