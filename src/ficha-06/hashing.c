#include "hashing.h"

#include <stdio.h>

#include "lista.c"

HASHING *criar_vetor_hashing() {
  HASHING *hashing = (HASHING *)malloc(sizeof(HASHING));
  if (!hashing) return NULL;

  hashing->vector = (GRUPO *)malloc(sizeof(GRUPO) * TAM_HASHING);
  if (!hashing->vector) {
    free(hashing);
    return NULL;
  }

  hashing->tam = TAM_HASHING;

  return hashing;
}

void inicializar_vetor_hashing(HASHING *hashing) {
  if (!hashing) return;

  for (int i = 0; i < hashing->tam; i++) {
    hashing->vector[i].lista = NULL;
    hashing->vector[i].faixa_etaria = 0;
  }
}

int posicao_hashing_elemento(ELEMENTO *e) {
  if (!e) return -1;
  return e->pessoa->idade % TAM_HASHING;
}

int validar_posicao_hashing(int pos) {
  return pos >= 0 && pos < TAM_HASHING;
}

void inserir_elemento_hashing(HASHING *hashing, ELEMENTO *elemento) {
  if (!hashing || !elemento) return;

  int pos = posicao_hashing_elemento(elemento);
  if (!validar_posicao_hashing(pos)) return;

  if (!hashing->vector[pos].lista) {
    hashing->vector[pos].faixa_etaria = elemento->pessoa->idade;
    hashing->vector[pos].lista = criar_lista();
  }

  inserir_elemento_ordenado(hashing->vector[pos].lista, elemento);
}

ELEMENTO *remover_elemento_hashing(HASHING *hashing, ELEMENTO *elemento) {
  if (!hashing || !elemento) return NULL;

  int pos = posicao_hashing_elemento(elemento);
  if (!validar_posicao_hashing(pos)) return NULL;

  return remover_elemento(hashing->vector[pos].lista, elemento);
}

ELEMENTO *pesquisar_elemento_hashing(HASHING *hashing, ELEMENTO *elemento) {
  if (!hashing || !elemento) return NULL;

  int pos = posicao_hashing_elemento(elemento);
  if (!validar_posicao_hashing(pos)) return NULL;

  return pesquisar_elemento(hashing->vector[pos].lista, elemento);
}

void mostrar_elementos_hashing(HASHING *hashing) {
  if (!hashing) return;

  for (int i = 0; i < hashing->tam; i++) {
    if (hashing->vector[i].lista) {
      printf("\n\nFaixa etária: %d\n", hashing->vector[i].faixa_etaria);
      mostrar_ordenado(hashing->vector[i].lista);
    }
  }

  printf("\n");
}
