#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#define MAX_NOME 21

/*
  1. Defina uma estrutura Pessoa, associando-lhe o tipo de dados *ptPESSOA, com os dados:
    a) Nome (20 caracteres);
    b) Idade em anos (inteiro);
    c) Peso em quilos (número real);
    d) Altura em metros (número real);
*/
typedef struct Pessoa {
  char nome[MAX_NOME];
  int idade;
  float peso, altura;
} PESSOA;

#endif  // PESSOA_H_INCLUDED
