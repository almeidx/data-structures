#include "list.h"

#include <stdio.h>

#include "../util/util.c"

LIST *create_list() {
  LIST *list = (LIST *)malloc(sizeof(LIST));
  list->head = list->tail = NULL;
  list->size = 0;
  return list;
}

/*
  2. Defina uma função ptELEMENTO criar_ELEMENTO () que crie (aloque e inicialize) um novo nodo da lista bi-ligada.
*/
NODE *create_node(char *text) {
  NODE *new_node = (NODE *)malloc(sizeof(NODE));
  if (!new_node) return NULL;

  new_node->info = (WORD *)malloc(sizeof(WORD));
  if (!new_node->info) {
    free(new_node);
    return NULL;
  }

  new_node->info->text = (char *)malloc(sizeof(char) * (strlen(text) + 1));
  if (!new_node->info->text) {
    free(new_node->info);
    free(new_node);
    return NULL;
  }

  strcpy(new_node->info->text, text);

  new_node->next = NULL;
  new_node->prev = NULL;

  return new_node;
}

/*
  3. Defina a função void inserir_elemento_ordenado (ptLISTA L, ptELEMENTO ele_novo) que insira um novo elemento de
  forma ordenada na lista bi-ligada.
*/
void insert_node_sorted(LIST *list, NODE *node) {
  if (!list) return;

  node->prev = node->next = NULL;

  if (!list->head) {
    list->head = node;
  } else {
    NODE *aux = list->head;
    int STOP = 1;

    while (aux && STOP) {
      if (!strcmp(aux->info->text, node->info->text)) {
        aux = aux->next;
      } else {
        STOP = 0;
      }
    }

    if (aux) {
      if (list->head == aux) {
        node->next = aux;
        aux->prev = node;
        list->head = node;
      } else {
        aux->prev->next = node;
        node->prev = aux->prev;
        node->next = aux;
        aux->prev = node;
      }
    } else {
      aux->next = node;
      node->prev = aux;
      node->next = NULL;
    }
  }

  list->size++;
  return;
}

/*
  4. Defina a função ptELEMENTO remover_elemento(ptLISTA L, ptELEMENTO ele_remover) de modo a suportar a atualização do
  apontador para o elemento anterior numa lista bi-ligada.
*/
NODE *remove_node(LIST *list, NODE *node) {
  if (!list || !node) return NULL;

  if (node->prev) {
    node->prev->next = node->next;
  } else {
    list->head = node->next;
  }

  if (node->next) {
    node->next->prev = node->prev;
  } else {
    list->tail = node->prev;
  }

  list->size--;
  return node;
}

/*
  5. Defina a função ptELEMENTO remover_primeiro(ptLISTA L) de modo a suportar a atualização do apontador para o
  elemento anterior numa lista bi-ligada.
*/
NODE *remove_first_node(LIST *list) {
  if (!list->head) return NULL;

  NODE *node = list->head;

  list->head = list->head->next;
  list->head->prev = NULL;
  list->size--;

  return node;
}

/*
  6. Defina uma função void mostrar_ordenado(ptLISTA L) que mostre os elementos pela ordem actual.
*/
void print_list(LIST *list) {
  if (!list) return;

  NODE *aux = list->head;
  while (aux) {
    printf("%s\n", aux->info->text);
    aux = aux->next;
  }
}

/*
  7. Defina uma função void mostrar_inversa(ptLISTA L) que mostre os elementos pela ordem inversa, tirando partido do
  ponteiro para o elemento anterior.
*/
void print_list_inverse(LIST *list) {
  if (!list) return;

  NODE *aux = list->tail;
  while (aux) {
    printf("%s\n", aux->info->text);
    aux = aux->prev;
  }
}

/*
  8. Defina uma função void mostrar_n_anteriores(ptLISTA L, ptELEMENTO ele_pesquisar, int n) que mostre os dados dos
  nós que antecedem uma dada palavra de uma lista
*/
void print_n_before_node(LIST *list, NODE *node, int n) {
  if (!list || !node) return;

  NODE *aux = node;
  while (aux && n > 0) {
    printf("%s\n", aux->info->text);
    aux = aux->prev;
    n--;
  }
}

void free_node(NODE *node) {
  if (!node) return;

  free(node->info->text);
  free(node->info);
  free(node);
}

void free_list(LIST *list) {
  if (!list) return;

  NODE *current = list->head, *previous;
  while (current) {
    previous = current;
    current = current->next;
    free_node(previous);
  }

  free(list);
}

void remove_word(LIST *list, char *text) {
  if (!list || !text) return;

  NODE *aux = list->head;
  while (aux && strcmp(aux->info->text, text) < 0) {
    aux = aux->next;
  }

  if (!aux) return;

  free_node(remove_node(list, aux));
}

NODE *search_node_by_word(LIST *list, char *text) {
  if (!list || !text) return NULL;

  NODE *aux = list->head;
  while (aux && strcmp(aux->info->text, text)) {
    aux = aux->next;
  }

  if (!aux || strcmp(aux->info->text, text)) return NULL;

  return aux;
}

/*
  9. No menu da aplicação, além das opções que lhe permitam executar as funcionalidades implementadas nas funções
  criadas, deve incluir também 3 opções que permitam mostrar o elemento actual, o próximo e o anterior e uma opção que
  permita inserir algumas palavras para teste.
*/

void wait_for_continue() {
  flush_stdin();

  printf("\n\nPress ENTER to continue...");
  getchar();
}

int menu(LIST *list) {
  int option;

  do {
    fflush(stdin);

    printf(
        "\n\n# MENU PRINCIPAL ---------------------------------------- #"
        "\n| (1) Inserir um novo elemento na lista                   |"
        "\n| (2) Retirar um elemento (especificado pelo utilizador)  |"
        "\n| (3) Retirar o primeiro elemento da lista                |"
        "\n| (4) Mostrar os elementos pela ordem actual              |"
        "\n| (5) Mostrar os elementos pela ordem inversa             |"
        "\n| (6) Listar n elementos anteriores a um elemento         |"
        "\n| (7) Mostrar elementos a volta                           |"
        "\n| (8) Inserir algumas palavras para teste                 |"
        "\n| ------------------------------------------------------- |"
        "\n| (0) SAIR                                                |"
        "\n# ------------------------------------------------------- #\n");

    scanf("%d", &option);
  } while (option < 0 || option > 8);

  switch (option) {
    case 1: {
      char text[MAX_WORD_SIZE];
      read_string(text, "Introduza a palavra para inserir: ");

      NODE *node = create_node(text);

      if (node) {
        insert_node_sorted(list, node);
      }

      break;
    }

    case 2: {
      char text[MAX_WORD_SIZE];
      read_string(text, "Introduza a palavra para remover: ");

      remove_word(list, text);
      break;
    }

    case 3:
      remove_first_node(list);
      break;

    case 4:
      print_list(list);
      break;

    case 5:
      print_list_inverse(list);
      break;

    case 6: {
      char text[MAX_WORD_SIZE];
      read_string(text, "Introduza a palavra para procurar: ");

      NODE *node = search_node_by_word(list, text);
      if (!node) break;

      print_n_before_node(list, node, read_int("Introduza o numero de elementos para mostrar: "));
      break;
    }

    case 7: {
      char text[MAX_WORD_SIZE];
      read_string(text, "Introduza a palavra para procurar: ");

      NODE *node = search_node_by_word(list, text);
      if (!node) break;

      if (node->prev) {
        printf("Previous: %s\n", node->prev->info->text);
      }

      printf("Current: %s\n", node->info->text);

      if (node->next) {
        printf("Next: %s\n", node->next->info->text);
      }

      break;
    }

    case 8: {
      insert_node_sorted(list, create_node("teste"));
      insert_node_sorted(list, create_node("ola"));
      insert_node_sorted(list, create_node("adeus"));
      insert_node_sorted(list, create_node("oi"));
      insert_node_sorted(list, create_node("palavra"));
      insert_node_sorted(list, create_node("voltar"));

      break;
    }

    case 0:
      return 1;
  }

  wait_for_continue();

  return 0;
}
