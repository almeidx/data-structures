#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic-list.c"

#define SUCCESS 1
#define FAILURE 0

#define MAX_CAPACITY 26

typedef struct Hashing {
  int capacity;
  LIST *array[MAX_CAPACITY];
} HASHING;

HASHING *create_hashing();
void destroy_hashing(HASHING *hashing);
int add_hashing(HASHING *hashing, char *data);
void show_hashing(HASHING *hashing);

int hash(HASHING *hashing, char *x);

#endif  // HASHING_H_INCLUDED
