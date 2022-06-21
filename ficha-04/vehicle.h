#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
  1. Defina uma estrutura de dados adequada para manter em memória RAM os seguintes dados relativos a uma determinada
  viatura:
    a) Matrícula (8 caracteres);
    b) Proprietário (30 caracteres);
    c) Marca (15 caracteres);
    d) Cor (15 caracteres);
    e) Tempo de entrada (time_t);
    f) Tempo de saída (time_t);
    g) Tempo de espera e lavagem em segundos (inteiro).
*/

#define MAX_PLATE 9
#define MAX_OWNER 31
#define MAX_MAKE 16
#define MAX_COLOUR 16

typedef struct Vehicle {
  char plate[MAX_PLATE];
  char owner[MAX_OWNER];
  char make[MAX_MAKE];
  char colour[MAX_COLOUR];
  time_t entered_at;
  time_t left_at;
  int wash_time;
} VEHICLE;

VEHICLE* read_vehicle();
void show_vehicle(VEHICLE* vehicle);
int compare_vehicles(VEHICLE* vehicle1, VEHICLE* vehicle2);
int get_wash_time(VEHICLE* vehicle);
void destroy_vehicle(VEHICLE* vehicle);

#endif  // VEHICLE_H_INCLUDED
