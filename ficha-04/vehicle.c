#include "vehicle.h"

#include "../util/util.c"

/*
  3. Escreva uma função que faça a leitura dos dados relativos a uma viatura que chega ao serviço de lavagens,
  procedendo também ao registo do tempo de entrada.
*/
VEHICLE* read_vehicle() {
  VEHICLE* vehicle = (VEHICLE*)malloc(sizeof(VEHICLE));

  read_string(vehicle->plate, "Insira a matricula do veiculo: ");
  read_string(vehicle->owner, "Insira o proprietario do veiculo: ");
  read_string(vehicle->make, "Insira a marca do veiculo: ");
  read_string(vehicle->colour, "Insira a cor do veiculo: ");

  vehicle->wash_time = read_int("Insira o tempo de espera do veiculo: ");
  vehicle->entered_at = time(NULL);

  return vehicle;
}

/*
  4. Escreva uma função que mostre os dados relativos a uma dada viatura em espera.
*/
void show_vehicle(VEHICLE* vehicle) {
  printf("---- Veiculo ----\n");
  printf("\tMatricula: %s\n", vehicle->plate);
  printf("\tProprietario: %s\n", vehicle->owner);
  printf("\tMarca: %s\n", vehicle->make);
  printf("\tCor: %s\n", vehicle->colour);
  printf("\tInstante de entrada: %d\n", ctime(&vehicle->entered_at));
  printf("\tInstante de saida: %d\n", ctime(&vehicle->left_at));
  printf("\tTempo de lavagem: %d\n", get_wash_time(vehicle));
}

int compare_vehicles(VEHICLE* vehicle1, VEHICLE* vehicle2) {
  return strcmp(vehicle1->plate, vehicle2->plate);
}

int get_wash_time(VEHICLE* vehicle) {
  return (int)difftime(vehicle->entered_at, vehicle->left_at);
}

void destroy_vehicle(VEHICLE* vehicle) {
  free(vehicle);
}
