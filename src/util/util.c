#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 128

typedef enum { false, true } bool;

typedef struct Data {
  int dia, mes, ano;
} DATE;

int read_int(char *msg) {
  int n;
  printf(msg);
  scanf("%d", &n);
  return n;
}

float read_float(char *msg) {
  float n;
  printf(msg);
  scanf("%f", &n);
  return n;
}

char read_char(char *msg) {
  char c;
  printf(msg);
  scanf("%c", &c);
  return c;
}

void read_string(char *str, char *msg) {
  printf(msg);
  scanf("%s", str);
}

// https://stackoverflow.com/a/33450696/11252146
void clear_terminal() {
  system("@cls||clear");
}

void flush_stdin() {
  fflush(stdin);
}

FILE *open_file(char *filename, char *mode) {
  FILE *f = fopen(filename, mode);
  if (f == NULL) {
    printf("Erro ao abrir o ficheiro %s\n", filename);
    exit(EXIT_FAILURE);
  }

  return f;
}

// https://stackoverflow.com/a/15768317/11252146
void rand_str(char *dest, size_t length) {
  char charset[] =
      "0123456789"
      "abcdefghijklmnopqrstuvwxyz"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  while (length-- > 0) {
    size_t index = (double)rand() / RAND_MAX * (sizeof charset - 1);
    *dest++ = charset[index];
  }

  *dest = '\0';
}

int rand_int(int min, int max) {
  return rand() % (max + 1 - min) + min;
}

void rand_date(DATE *date) {
  date->dia = rand_int(1, 31);
  date->mes = rand_int(1, 12);
  date->ano = rand_int(2010, 2022);
}
