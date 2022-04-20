#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "pessoa.h"

/*
  2. Defina uma estrutura Elemento, associando-lhe o tipo de dados *ptELEM, adequada para a construção de uma lista
  ligada de elementos e com um campo do tipo ptPESSOA.
*/
typedef struct Elemento {
  PESSOA *pessoa;
  struct Elemento *prox;
} ELEMENTO;

/*
  3. Defina uma estrutura Lista, associando-lhe o tipo de dados *ptLISTA, com os dados:
    a) Número de elementos (inteiro);
    b) Elemento inicial da lista.
*/
typedef struct Lista {
  ELEMENTO *inicio;
  int tam;
} LISTA;

/*
  6. Escreva uma função ptLISTA criarLista() que crie (aloque e inicialize) uma lista de elementos.
*/
LISTA *criar_lista();

/*
  7. Escreva uma função ptELEM criar_elemento() que crie (aloque e inicialize) um novo elemento.
*/
ELEMENTO *criar_elemento();

/*
  8. Escreva uma função void ler_elemento(ptELEM ele_novo) que registe os dados de um dado elemento
*/
ELEMENTO *ler_elemento(ELEMENTO *elemento);

/*
  9. Escreva uma função int comparar_elementos(ptELEM A, ptELEM B) que compare dois elementos, recorrendo ao campo idade
  da pessoa associada.
*/
int comparar_elementos(ELEMENTO *elem1, ELEMENTO *elem2);

/*
  10. Escreva uma função int elementos_iguais(ptELEM A, ptELEM B) que verifique a igualdade entre dois elementos.
*/
int elementos_iguais(ELEMENTO *elem1, ELEMENTO *elem2);

/*
  11. Escreva uma função void inserir_elemento_ordenado(ptLISTA L, ptELEM ele_novo) que introduza um elemento na lista,
  garantido a sua ordenação através do campo idade da pessoa.
*/
void inserir_elemento_ordenado(LISTA *lista, ELEMENTO *elemento);

/*
  12. Escreva uma função ptELEM pesquisar_elemento(ptLISTA L, ptELEM ele_pesquisa) que verifique se um determinado
  elemento pertence a uma lista utilizando uma abordagem iterativa.
*/
ELEMENTO *pesquisar_elemento(LISTA *lista, ELEMENTO *elemento);

/*
  13. Escreva uma função void libertar_elemento(ptELEM ele_libertar) que liberte o espaço alocado para um dado elemento
  e respetivas informações associadas.
*/
void libertar_elemento(ELEMENTO *elemento);

/*
  14. Escreva uma função ptELEM remover_elemento(ptLISTA L, ptELEM ele_remover) que remova um determinado elemento de
  uma lista.
*/
ELEMENTO *remover_elemento(LISTA *lista, ELEMENTO *elemento);

/*
  15. Escreva uma função void mostrar_elemento(ptELEM ele_mostrar) que mostre os dados de uma pessoa.
*/
void mostrar_elemento(ELEMENTO *elemento);

/*
  16. Escreva uma função void mostrar_ordenado(ptLISTA L) que mostre os dados de todos os elementos de uma lista pela
  ordem actual.
*/
void mostrar_ordenado(LISTA *lista);

#endif  // LISTA_H_INCLUDED
