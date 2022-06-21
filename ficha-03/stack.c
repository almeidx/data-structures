#include "stack.h"

STACK *create_stack() {
  STACK *s = (STACK *)malloc(sizeof(STACK));
  s->top = NULL;
  s->size = 0;
  return s;
}

/*
  5. Escreva uma função que permita inserir um contentor no topo da pilha.
*/
void push_to_stack(STACK *stack, CONTAINER *data) {
  NODE *new_node = (NODE *)malloc(sizeof(NODE));
  new_node->data = data;
  new_node->next = stack->top;
  stack->top = new_node;

  printf("tmp: %d", stack->size);

  stack->size++;
}

/*
  6. Escreva uma função que permita retirar um contentor do topo da pilha.
*/
CONTAINER *pop_stack(STACK *stack) {
  if (!stack || !stack->size) return NULL;

  CONTAINER *data = stack->top->data;
  NODE *aux = stack->top;

  stack->top = stack->top->next;

  free(aux);

  stack->size--;

  return data;
}

/*
  7. Escreva uma função que permita saber quantos contentores tem uma pilha.
*/
int get_stack_size(STACK *stack) {
  if (!stack) return -1;
  return stack->size;
}

/*
  8. Escreva uma função que permita saber qual o contentor que se encontra no fundo da pilha.
*/
CONTAINER *get_bottom_container(STACK *s) {
  if (!s || !s->top) return NULL;

  NODE *current = s->top;

  while (current->next) {
    current = current->next;
  }

  return current->data;
}

CONTAINER *top_of_stack(STACK *stack) {
  if (!stack || !stack->size) return NULL;
  return stack->top->data;
}

void show_stack(STACK *stack, void (*show_container)(CONTAINER *)) {
  if (!stack || !stack->size) return;

  NODE *aux = stack->top;

  printf("------ Stack ------\n");

  while (aux) {
    show_container(aux->data);
    aux = aux->next;
  }
}

void destroy_stack(STACK *stack) {
  if (!stack || !stack->size) return;
  NODE *aux = stack->top, *aux2;

  while (aux) {
    aux2 = aux->next;
    free(aux);
    aux = aux2;
  }

  free(stack);
}

void print_missing_stack_error() {
  printf("A pilha ainda nao foi criada.\n");
}

void wait_for_continue() {
  flush_stdin();

  printf("\n\nPress ENTER to continue...");
  getchar();
}

/*
  9. Escreva uma função menu() que oriente o utilizador do programa na escolha das diferentes funcionalidades que lhe
  são proporcionadas.

  Retorna 1 se o utilizador quiser sair, caso contrario retorna 0
*/
int menu(STACK *stack) {
  int option, should_wait_for_continue = 1;

  do {
    flush_stdin();

    printf(
        "(1) Inserir elemento no topo\n"
        "(2) Retirar o elemento do topo\n"
        "(3) Mostrar o elemento do fundo\n"
        "(4) Mostrar o numero de elementos\n"
        "(5) Mostrar pilha\n"
        "(0) SAIR\n");

    scanf("%d", &option);
  } while (option < 0 || option > 6);

  switch (option) {
    case 1: {
      CONTAINER *c = create_container();
      if (!c) {
        printf("Failed to create container");
        break;
      }

      push_to_stack(stack, c);

      should_wait_for_continue = 0;
      break;
    }

    case 2:
      pop_stack(stack);
      break;

    case 3: {
      CONTAINER *c = get_bottom_container(stack);
      if (!c) break;
      show_container(c);
      break;
    }

    case 4:
      printf("A pilha tem %d elementos", get_stack_size(stack));
      break;

    case 5:
      show_stack(stack, show_container);
      break;

    case 0:
      return 1;
  }

  if (should_wait_for_continue) {
    wait_for_continue();
  }

  return 0;
}
