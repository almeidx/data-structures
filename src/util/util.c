#include <stdio.h>

typedef enum { false, true } bool;

int readInt(char *msg) {
  int n;
  printf(msg);
  scanf("%d", &n);
  return n;
}

float readFloat(char *msg) {
  float n;
  printf(msg);
  scanf("%f", &n);
  return n;
}

char readChar(char *msg) {
  char c;
  printf(msg);
  scanf("%c", &c);
  return c;
}

void readString(char *str, char *msg) {
  printf(msg);
  scanf("%s", str);
}
