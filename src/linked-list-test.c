#include "./util/linked-list.c"

#include <stdio.h>
#include <stdlib.h>

void print_vehicle(VEHICLE *v) {
  printf("Vehicle:\n");
  printf("  Chassi: %d\n", v->chassi);
  printf("  Year: %d\n", v->year);
}

VEHICLE *create_vehicle(int chassi, int year) {
  VEHICLE *v = (VEHICLE *)malloc(sizeof(VEHICLE));
  v->chassi = chassi;
  v->year = year;
  return v;
}

void main() {
  LIST *list = create_list();
  VEHICLE *vehicle = create_vehicle(123, 2018);

  prepend_to_list(list, vehicle);

  show_list(list);

  search_chassi(list, 1111);

  free_list(list);
}
