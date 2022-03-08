#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/matrix.c"
#include "../util/util.c"

/*
  1. Desenvolva uma função que dada uma matriz bidimensional MxN de inteiros indique se é esparsa. Se a matriz for
  esparsa é retornado 1 senão é retornado 0. Uma matriz é esparsa, se a percentagem de elementos nulos estiverem acima
  de um determinado limite (percentagem).
 */
int Esparsa(int *Matriz, int M, int N, float percentagem) {
  int i, j, nulos = 0;

  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      if (Matriz[i * N + j] == 0) {
        nulos++;
      }
    }
  }

  if ((float)nulos / (M * N) > percentagem) {
    return 1;
  } else {
    return 0;
  }
}

void main() {
  int rows = readInt("Qual é o número de linhas da matriz?\n"),
      cols = readInt("Qual é o número de colunas da matriz?\n");

  int *matrix = (int *)malloc(cols * rows * sizeof(int));

  float percentage = readFloat("Qual é a percentagem de elementos nulos?\n");

  readMatrix(matrix, rows, cols);

  printMatrix(matrix, rows, cols);

  if (Esparsa(matrix, rows, cols, 0.2)) {
    printf("A matriz é esparsa\n");
  } else {
    printf("A matriz não é esparsa\n");
  }

  free(matrix);
}
