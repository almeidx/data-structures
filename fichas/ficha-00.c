#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 128
#define FICHEIRO_MUSICAS "musicas.dat"

typedef enum { false, true } bool;

int readInt(int *n, char *msg) {
  printf(msg);
  scanf("%d", n);
}

float readFloat(float *n, char *msg) {
  printf(msg);
  scanf("%f", n);
}

void readString(char *str, char *msg) {
  printf(msg);
  scanf("%s", str);
}

char readChar(char *c, char *msg) {
  printf(msg);
  scanf("%c", c);
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

/*
  Pretende-se analisar um conjunto de músicas. Cada música caracteriza-se pelo título, intérprete, ano, single (1:sim ou
  0:não) e número de downloads nas plataformas aderentes.

  Obs. 1. n, em todos os cabeçalhos das funções, representa o número de músicas no vetor lista;
  2. utilize ponteiros em todas as alíneas para aceder ao valor dos atributos dos elementos do vetor.
*/

/*
  a) Defina o tipo de dados MUSIC e crie um vetor de nome lista, com um número de músicas definido pelo utilizador
  (valor disponível na variável nMusicas).
*/
typedef struct {
  char titulo[STRING_LENGTH], interprete[STRING_LENGTH];
  short ano;
  /** 1:sim ou 0:não */
  short single;
  int downloads;
} MUSIC;

void readMusic(MUSIC *music) {
  printf("Qual é o titulo da música?\n");
  scanf("%s", music->titulo);

  printf("Qual é o nome do artista?\n");
  scanf("%s", music->interprete);

  printf("Qual é o ano de lançamento?\n");
  scanf("%hd", &music->ano);

  printf("É single? (1:sim ou 0:não)\n");
  scanf("%hd", &music->single);

  printf("Quantos downloads teve a música?\n");
  scanf("%d", &music->downloads);
}

/*
  b) Implemente uma função que escreva no ecrã, as características das músicas com mais do que um determinado número de
  downloads (parâmetro numD).
  void musicasDownload(MUSIC *lista, int n, int numD)
*/
void musicasDownload(MUSIC *lista, int n, int numD) {
  bool captionShown = false;
  for (int i = 0; i < n; i++) {
    if (lista[i].downloads > numD) {
      if (!captionShown) {
        printf("Título | Intérprete | Ano | Single | Downloads\n");
        captionShown = true;
      }

      printf("%s | %s | %d | %d\n", lista[i].titulo, lista[i].interprete, lista[i].ano, lista[i].downloads);
    }
  }
}

/*
  c) Desenvolva uma função que receba a listagem de músicas e devolva quantas têm um dado intérprete.
*/
int quantidadeDeInterprete(MUSIC *lista, int n, char *interprete) {
  int qnt = 0;
  for (int i = 0; i < n; i++) {
    if (!strcmp(lista[i].interprete, interprete)) {
      qnt++;
    }
  }
  return qnt;
}

/*
  d) Desenvolva uma função que guarde num ficheiro binário, as músicas singles, não singles ou ambas (parâmetro
  tpMeio=’s’, ‘n’ ou ‘a´, respetivamente), posteriores a um determinado ano. A função deve ainda devolver o número médio
  de downloads dessas músicas.
  float gravaFichMusicas (MUSIC *lista, int n, int ano, char *nFich, char tpMeio)

  Obs. Sintaxes:
  FILE* fopen(const char* fileName, const char* mode);
  size_t fwrite (                                 const void* ptr, size_t size, size_t nElements, FILE* file);
*/
float gravaFichMusicas(MUSIC *lista, int n, int ano, char *nFich, char tpMeio) {
  FILE *f = fopen(nFich, "wb");
  if (f == NULL) {
    printf("Erro ao abrir o ficheiro %s\n", nFich);
    return 0.0f;
  }

  int totalDownloads = 0, nMusicas = 0;

  for (int i = 0; i < n; i++) {
    if (lista[i].ano > ano) {
      if (((tpMeio == 's' || tpMeio == 'a') && lista[i].single) ||
          ((tpMeio == 'n' || tpMeio == 'a') && !lista[i].single)) {
        fwrite(&lista[i].titulo, sizeof(MUSIC), 1, f);
        totalDownloads += lista[i].downloads;
        nMusicas++;
      }
    }
  }

  fclose(f);

  return totalDownloads / n;
}

void main() {
  // Exercicio 1
  // int rows, cols;
  // readInt(&rows, "Qual é o número de linhas da matriz?\n")
  // readInt(&cols, "Qual é o número de colunas da matriz?\n")

  // int *matrix = (int *)malloc(cols * rows * sizeof(int));

  // float percentage;
  // readFloat(&percentage, "Qual é a percentagem de elementos nulos?\n")

  // readMatrix(matrix, rows, cols);

  // printMatrix(matrix, rows, cols);

  // if (Esparsa(matrix, rows, cols, 0.2)) {
  //   printf("A matriz é esparsa\n");
  // } else {
  //   printf("A matriz não é esparsa\n");
  // }

  // free(matrix);

  // Exercicio 2
  // a
  int n;
  readInt(&n, "Qual é o número de musicas?\n");

  MUSIC *musicas = (MUSIC *)malloc(n * sizeof(MUSIC));

  for (int i = 0; i < n; i++) {
    readMusic(musicas + i);
  }

  // b
  int nDownloads;
  readInt(&nDownloads, "Qual é o minimo de downloads?\n");

  musicasDownload(musicas, n, nDownloads);

  // c;
  char interprete[STRING_LENGTH];
  readString(interprete, "Qual é o nome do intérprete?\n");

  printf("Há %d musicas com o interprete %s.\n", quantidadeDeInterprete(musicas, n, interprete), interprete);

  // d
  int ano;
  readInt(&ano, "Qual é o ano?\n");

  char single;

  do {
    readChar(&single, "Singles (s), não singles (n), ou ambos (a)?");
  } while (single != 's' && single != 'n' && single != 'a');

  printf("Número médio de downloads: %.2f", gravaFichMusicas(musicas, n, ano, FICHEIRO_MUSICAS, single));
}
