#include "container.h"

#include "../util/date.c"
#include "../util/util.c"

/*
  3. Escreva uma função que faça o registo dos dados relativos a um contentor que chega ao armazém. Esta função deve
  inserir a data do sistema.
*/
CONTAINER *create_container() {
  CONTAINER *c = (CONTAINER *)malloc(sizeof(CONTAINER));
  if (!c) return NULL;

  read_string(c->content, "Insira o conteudo do contentor: ");
  read_string(c->client, "Insira o nome do cliente do contentor: ");
  read_string(c->destination, "Insira o destino do contentor: ");
  read_string(c->origin, "Insira a origem do contentor: ");
  read_string(c->referencia, "Insira a referencia do contentor: ");

  c->entry_date = get_current_date();

  return c;
}

/*
  4. Escreva uma função que permita visualizar os dados relativos aos contentores que se encontram em armazém.
*/
void show_container(CONTAINER *c) {
  printf("Contentor:\n");
  printf("\tConteudo: %s\n", c->content);
  printf("\tCliente: %s\n", c->client);
  printf("\tDestino: %s\n", c->destination);
  printf("\tOrigem: %s\n", c->origin);
  printf("\tData de entrada: %d/%d/%d\n", c->entry_date->day, c->entry_date->month, c->entry_date->year);
}
