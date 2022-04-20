#include "hashing.h"

#include <stdio.h>

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

void inserir_elemento_hashing(HASHING *hashing, ELEMENTO *elemento) {}

ELEMENTO *remover_elemento_hashing(HASHING *hashing, ELEMENTO *elemento) {}

ELEMENTO *pesquisar_elemento_hashing(HASHING *hashing, ELEMENTO *elemento) {}

void mostrar_elementos_hashing(HASHING *hashing) {}
