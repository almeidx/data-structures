#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#include "../util/date.c"

/*
  1. Defina uma estrutura de dados adequada para manter em memória RAM os seguintes dados relativos a um contentor
armazenado:
  a) Conteúdo (80 caracteres);
  b) Origem (30 caracteres);
  c) Destino (15 caracteres);
  d) Cliente (80 caracteres);
  e) Data de entrada (do sistema [ano, mes, dia]);
  f) Tonelagem (número real);
  g) Referência (15 caracteres).
*/

#define MAX_CONTENT 81
#define MAX_ORIGIN 31
#define MAX_DESTINATION 16
#define MAX_CLIENT 81
#define MAX_REFERENCE 16

typedef struct Container {
  char content[MAX_CONTENT];
  char origin[MAX_ORIGIN];
  char destination[MAX_DESTINATION];
  char client[MAX_CLIENT];
  DATE *entry_date;
  float tonelagem;
  char referencia[MAX_REFERENCE];
} CONTAINER;

CONTAINER *create_container();
void show_container(CONTAINER *container);

#endif  // CONTAINER_H_INCLUDED
