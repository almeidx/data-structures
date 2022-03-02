#include <stdio.h>
#include <stdlib.h>

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

void readMatrix(int *matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("matriz[%d][%d]: ", i, j);
      scanf("%d", &matrix[i * cols + j]);
    }
  }
}

void printMatrix(int *matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", matrix[i * cols + j]);
    }
    printf("\n");
  }
}

/*
 1. Desenvolva uma função que dada uma matriz bidimensional MxN de inteiros indique se é esparsa. Se a matriz for
 esparsa é retornado 1 senão é retornado 0. Uma matriz é esparsa, se a percentagem de elementos nulos estiverem acima de
 um determinado limite (percentagem).
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

/*
Pretende-se analisar um conjunto de músicas. Cada música caracteriza-se pelo título, intérprete, ano, single (1:sim ou
0:não) e número de downloads nas plataformas aderentes.

Obs. 1. n, em todos os cabeçalhos das funções, representa o número de músicas no vetor lista;
2. utilize ponteiros em todas as alíneas para aceder ao valor dos atributos dos elementos do vetor.

a) Defina o tipo de dados Musica e crie um vetor de nome lista, com um número de músicas definido pelo utilizador (valor
disponível na variável nMusicas).

b) Implemente uma função que escreva no ecrã, as características das músicas com mais do que um determinado número de
downloads (parâmetro numD). void musicasDownload(Musica *lista, int n, int numD)

c) Desenvolva uma função que receba a listagem de músicas e devolva quantas têm um dado intérprete.

d) Desenvolva uma função que guarde num ficheiro binário, as músicas singles, não singles ou ambas (parâmetro
tpMeio=’s’, ‘n’ ou ‘a´, respetivamente), posteriores a um determinado ano. A função deve ainda devolver o número médio
de downloads dessas músicas.
float gravaFichMusicas (Musica *lista, int n, int ano, char *nFich, char tpMeio)

Obs. Sintaxes: FILE* fopen(const char* fileName, const char* mode); size_t fwrite (const void* ptr, size_t size, size_t
nElements, FILE* file);
*/

void main() {
  // Exercicio 1
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

  // Exercicio 2
}
