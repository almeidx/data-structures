#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

#include "lista.h"

/*
  4. Defina uma estrutura Grupo, com os dados:
    a) Faixa etária (inteiro);
    b) Lista de pessoas (ptLISTA);
*/
typedef struct Grupo {
  int faixa_etaria;
  LISTA *lista;
} GRUPO;

/*
  5. Defina uma estrutura Hashing, associando-lhe o tipo de dados *ptHASHING, com um campo vector que contém 10
  elementos do tipo GRUPO, que irão representar faixas etárias distintas dos 0 aos 100 anos em intervalos consecutivos
  de 10 anos.
*/
#define TAM_HASHING 10

typedef struct Hashing {
  GRUPO *vector;
  int tam;
} HASHING;

/*
  17. Escreva uma função ptHASHING criar_vector_hashing() que crie (aloque) um vector de hashing.
*/
HASHING *criar_vetor_hashing();

/*
  18. Escreva uma função void inicializar_vector_hashing(ptHASHING H) que inicialize um vector de hashing.
*/
void inicializar_vetor_hashing(HASHING *hashing);

/*
  19. Escreva uma função int posicao_hashing_elemento(ptELEM E) que calcule a posição de hashing correcta para um dado
  elemento.
*/
int posicao_hashing_elemento(ELEMENTO *e);

/*
  20. Escreva uma função int validar_posicao_hashing(int pos) que valide uma posição de hashing calculada através da
  função do ponto anterior.
*/
int validar_posicao_hashing(int pos);

/*
  21. Escreva uma função void inserir_elemento_hashing(ptHASHING H, ptELEM E) que introduza um dado elemento num vector
  de hashing.
*/
void inserir_elemento_hashing(HASHING *hashing, ELEMENTO *elemento);

/*
  22. Escreva uma função ptELEM remover_elemento_hashing(ptHASHING H, ptELEM ele_remover) que remova um elemento de um
  vector de hashing.
*/
ELEMENTO *remover_elemento_hashing(HASHING *hashing, ELEMENTO *elemento);

/*
  23. Escreva uma função ptELEM pesquisar_elemento_hashing(ptHASHING H, ptELEM ele_pesquisa) que pesquise por um
  elemento num vector de hashing.
*/
ELEMENTO *pesquisar_elemento_hashing(HASHING *hashing, ELEMENTO *elemento);

/*
  24. Escreva uma função void mostrar_elementos_hashing(ptHASHING H) que imprima os dados de todos os elementos que
  constam do vector de hashing.
*/
void mostrar_elementos_hashing(HASHING *hashing);

#endif  // HASHING_H_INCLUDED
