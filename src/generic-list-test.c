#include "generic-list-test.h"

#include "./util/generic-list.c"

void main() {
  LIST *list = create_list();
  CAR *c = create_car("BMW", 2020);
  add_to_list(list, c);
  c = create_car("Audi", 2019);
  add_to_list(list, c);
  show_list(list, show_car);
  destroy_list(list, destroy_car);

  printf("\n");

  list = create_list();
  PRODUCT *p = create_product("TV", 2000.5f, 26);
  add_to_list(list, p);
  p = create_product("Legion 5 Pro", 1300.0f, 26);
  add_to_list(list, p);
  show_list(list, show_product);
  destroy_list(list, destroy_product);
}

CAR *create_car(char *make, int year) {
  CAR *car = (CAR *)malloc(sizeof(CAR));
  if (!car) return NULL;

  strcpy(car->make, make);
  car->year = year;

  return car;
}

void show_car(void *car) {
  printf("-----[%s]-----\n", __FUNCTION__);
  CAR *c = (CAR *)car;

  printf("\tMake: %s\n", c->make);
  printf("\tYear: %d\n", c->year);
}

void destroy_car(void *car) {
  CAR *c = (CAR *)car;
  free(c);
}

PRODUCT *create_product(char *name, float price, int IVA) {
  PRODUCT *product = (PRODUCT *)malloc(sizeof(PRODUCT));
  if (!product) return NULL;

  strcpy(product->name, name);
  product->price = price;
  product->IVA = IVA;

  return product;
}

void show_product(void *product) {
  printf("-----[%s]-----\n", __FUNCTION__);
  PRODUCT *p = (PRODUCT *)product;

  printf("\tName: %s\n", p->name);
  printf("\tPrice: %.2f\n", p->price);
  printf("\tIVA: %d\n", p->IVA);
}

void destroy_product(void *product) {
  PRODUCT *p = (PRODUCT *)product;
  free(p);
}
