#ifndef GENERIC_LIST_TEST_H_INCLUDED
#define GENERIC_LIST_TEST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Car {
  char make[20];
  int year;
} CAR;

typedef struct Product {
  char name[20];
  float price;
  int IVA;
} PRODUCT;

CAR *create_car(char *make, int year);
void show_car(void *car);
void destroy_car(void *car);

PRODUCT *create_product(char *name, float price, int IVA);
void show_product(void *product);
void destroy_product(void *product);

#endif  // GENERIC_LIST_TEST_H_INCLUDED
