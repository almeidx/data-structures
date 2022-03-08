#include "../util/matrix.c"
#include "../util/util.c"

/*
  1. Desenvolva uma função que dada uma matriz bidimensional MxN de inteiros indique se é esparsa. Se a matriz for
  esparsa é retornado 1 senão é retornado 0. Uma matriz é esparsa, se a percentagem de elementos nulos estiverem acima
  de um determinado limite (percentagem).
 */
int matrix_esparsa(int *Matriz, int M, int N, float percentagem) {
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
  int rows = read_int("Qual é o número de linhas da matriz?\n"),
      cols = read_int("Qual é o número de colunas da matriz?\n");

  int *matrix = (int *)malloc(cols * rows * sizeof(int));

  float percentage = read_float("Qual é a percentagem de elementos nulos?\n");

  read_matrix(matrix, rows, cols);

  print_matrix(matrix, rows, cols);

  if (matrix_esparsa(matrix, rows, cols, 0.2)) {
    printf("A matriz é esparsa\n");
  } else {
    printf("A matriz não é esparsa\n");
  }

  free(matrix);
}
