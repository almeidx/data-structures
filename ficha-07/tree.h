#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

/*
  1. Defina uma estrutura Pessoa, associando-lhe o tipo de dados *ptPESSOA, com os seguintes dados:
    a) Nome (20 caracteres);
    b) Idade em anos (inteiro);
    c) Peso em quilos (número real);
    d) Altura em metros (número real);
*/
#define MAX_NOME 21

typedef struct pessoa {
  char nome[MAX_NOME];
  int idade;
  float peso, altura;
} PESSOA;

/*
  2. Defina uma estrutura No, associando-lhe o tipo de dados *ptNO, adequada para a construção de uma árvore binária de
elementos e com um campo informação do tipo ptPESSOA.
*/
typedef struct Node {
  PESSOA *info;
  struct Node *left, *right;
} NODE;

/*
  3. Defina uma estrutura Arvore, associando-lhe o tipo de dados *ptARVORE, com os dados:
    a) Número de nós (inteiro);
    b) Nó raiz da árvore (ptNO).
*/
typedef struct Tree {
  int size;
  NODE *root;
} TREE;

/*
  4. Escreva uma função ptARVORE criar_arvore() que crie (aloque e inicialize) uma árvore binária.
*/
TREE *criar_arvore();

/*
  5. Escreva uma função ptNO criar_no() que crie (aloque e inicialize) um novo nó.
*/
NODE *criar_no();

/*
  6. Escreva uma função void ler_no(ptNO N) que registe os dados de um dado nó.
*/
void ler_no(NODE *no);

/*
  7. Escreva uma função int comparar_nos(ptNO A, ptNO B) que compare dois nós, utilizando como único critério de
comparação a idade das pessoas associadas.
*/
int comparar_nos(NODE *A, NODE *B);

/*
  8. Escreva uma função int nos_iguais(ptNO A, ptNO B) que verifique a igualdade entre dois nós, utilizando como único
critério de comparação a idade das pessoas associadas.
*/
int nos_iguais(NODE *A, NODE *B);

/*
  9. Escreva uma função void inserir_no(ptNO no_novo, ptARVORE A) que introduza um nó na árvore, sendo a sua ordenação
dada pelo campo idade da pessoa.
*/
void inserir_no(TREE *tree, NODE *no_novo);

/*
  10. Escreva uma função ptNO pesquisar(int idade, ptARVORE A) que verifique se existe alguma pessoa com uma determinada
idade na árvore.
*/
NODE *pesquisar(TREE *tree, int idade);

/*
  11. Escreva uma função void mostrar_no(ptNO no_mostrar) que mostre os dados de um determinado nó.
*/
void mostrar_no(NODE *no_mostrar);

/*
  12. Escreva funções que permitam realizar a travessia da árvore binária, mostrando a informação
  de todos os nós, segundo:
    a) a técnica inorder - void mostrarInOrder(ptARVORE A)
    b) a técnica preorder - void mostrarPreOrder(ptARVORE A)
    c) a técnica postorder - void mostrarPostOrder(ptARVORE A)
*/
void mostrar_in_order(TREE *tree);
void mostrar_pre_order(TREE *tree);
void mostrar_post_order(TREE *tree);

/*
  13. Escreva uma função void libertar_no(ptNO no_libertar) que liberte o espaço alocado para um dado nó e respetivas
  informações associadas.
*/
void libertar_no(NODE *no_libertar);

/*
  14. Escreva uma função ptNO remover(ptNO no_remover, ptNO *raiz) que remova um dado nó de uma árvore, utilizando o
  campo idade como chave.
*/
NODE *remover(NODE *no_remover, NODE **raiz);

/*
  15. Escreva uma função int contar_nos(ptARVORE A) que calcule a quantidade de nós existentes numa dada árvore.
*/
int contar_nos(TREE *tree);

/*
  16. Escreva uma função int contar_nos_sup_idade(ptARVORE A, int idade_min) que determine o número de pessoas com um
  idade superior a uma determinada idade mínima.
*/
int contar_nos_sup_idade(TREE *tree, int idade_min);

/*
  17. Escreva uma função int contar_nos_inf_peso(ptARVORE A, float peso_max) que determine o número de pessoas com um
  peso inferior a um determinado peso máximo.
*/
int contar_nos_inf_peso(TREE *tree, float peso_max);

/*
  18. Escreva uma função int altura_arvore(ptARVORE A) que determine a altura de uma dada árvore.
*/
int altura_arvore(TREE *tree);

NODE *get_node_root(NODE *root, NODE *node);

void _show_tree_preorder(NODE *node);

void _show_tree_inorder(NODE *node);

void _show_tree_postorder(NODE *node);

void _count_tree_sup_idade(NODE *root, int idade_min, int *amount);

void _count_tree_inf_idade(NODE *root, int idade_min, int *amount);

int _height_tree(NODE *root);

#endif  // TREE_H_INCLUDED
