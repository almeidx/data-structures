#include "lista.h"

#include <stdio.h>

#include "../util/util.c"

LISTA *criar_lista() {
  LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
  if (!lista) return NULL;

  lista->inicio = NULL;
  lista->tam = 0;

  return lista;
}

ELEMENTO *criar_elemento() {
  ELEMENTO *elemento = (ELEMENTO *)malloc(sizeof(ELEMENTO));
  if (!elemento) return NULL;

  elemento->pessoa = NULL;
  elemento->prox = NULL;

  return elemento;
}

ELEMENTO *ler_elemento(ELEMENTO *elemento) {
  if (!elemento) return NULL;

  elemento->pessoa = (PESSOA *)malloc(sizeof(PESSOA));
  if (!elemento->pessoa) return NULL;

  char *nome = (char *)malloc(sizeof(char) * MAX_NOME);
  if (!nome) {
    free(elemento->pessoa);
    return NULL;
  }

  read_string(nome, "Insira o nome: ");
  realloc(elemento->pessoa->nome, sizeof(char) * MAX_NOME);

  elemento->pessoa->idade = read_int("Insira a idade: ");
  elemento->pessoa->peso = read_float("Insira o peso: ");
  elemento->pessoa->altura = read_float("Insira a altura: ");

  return elemento;
}

int comparar_elementos(ELEMENTO *elem1, ELEMENTO *elem2) {
  if (!elem1 || !elem2) return -1;
  return strcmp(elem1->pessoa->nome, elem2->pessoa->nome);
}

int elementos_iguais(ELEMENTO *elem1, ELEMENTO *elem2) {
  return !comparar_elementos(elem1, elem2);
}

void inserir_elemento_ordenado(LISTA *lista, ELEMENTO *elemento) {
  if (!lista || !elemento) return;

  ELEMENTO *elem_ant = NULL, *elem_atual = lista->inicio;

  while (elem_atual && comparar_elementos(elemento, elem_atual) > 0) {
    elem_ant = elem_atual;
    elem_atual = elem_atual->prox;
  }

  if (!elem_ant) {
    elemento->prox = lista->inicio;
    lista->inicio = elemento;
  } else {
    elemento->prox = elem_ant->prox;
    elem_ant->prox = elemento;
  }

  lista->tam++;
}

ELEMENTO *pesquisar_elemento(LISTA *lista, ELEMENTO *elemento) {
  if (!lista || !elemento) return NULL;

  ELEMENTO *elem_atual = lista->inicio;

  while (elem_atual && !elementos_iguais(elem_atual, elemento)) {
    elem_atual = elem_atual->prox;
  }

  return elem_atual;
}

void libertar_elemento(ELEMENTO *elemento) {
  if (!elemento) return;
  free(elemento->pessoa->nome);
  free(elemento->pessoa);
  free(elemento);
}

ELEMENTO *remover_elemento(LISTA *lista, ELEMENTO *elemento) {
  if (!lista || !elemento) return NULL;

  ELEMENTO *elem_ant = NULL, *elem_atual = lista->inicio;

  while (elem_atual && !elementos_iguais(elem_atual, elemento)) {
    elem_ant = elem_atual;
    elem_atual = elem_atual->prox;
  }

  if (!elem_atual) return NULL;

  if (!elem_ant) {
    lista->inicio = elem_atual->prox;
  } else {
    elem_ant->prox = elem_atual->prox;
  }

  lista->tam--;

  return elem_atual;
}

void mostrar_elemento(ELEMENTO *elemento) {
  if (!elemento) return;

  printf("Pessoa:\n");
  printf("\tNome: %s\n", elemento->pessoa->nome);
  printf("\tIdade: %d\n", elemento->pessoa->idade);
  printf("\tPeso: %.2f\n", elemento->pessoa->peso);
  printf("\tAltura: %.2f\n", elemento->pessoa->altura);
}

void mostrar_ordenado(LISTA *lista) {
  if (!lista) return;

  ELEMENTO *elem_atual = lista->inicio;

  while (elem_atual) {
    mostrar_elemento(elem_atual);
    elem_atual = elem_atual->prox;
  }
}
