#include <stdio.h>

typedef struct Data {
  int dia, mes, ano;
} DATA;

int read_int(char *msg);

float read_float(char *msg);

char read_char(char *msg);

void read_string(char *str, char *msg);

void clear_terminal();

FILE *open_file(char *fileName, char *mode);

void rand_str(char *dest, size_t length);

void rand_date(DATA date);
