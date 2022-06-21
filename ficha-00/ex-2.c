#include "../util/util.c"

#define FICHEIRO_MUSICAS "musicas.dat"

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

void read_music(MUSIC *music) {
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
void musicas_download(MUSIC *lista, int n, int numD) {
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
int quantidade_de_interprete(MUSIC *lista, int n, char *interprete) {
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
float grava_ficheiro_musicas(MUSIC *lista, int n, int ano, char *nome_ficheiro, char tipo_medio) {
  FILE *f = fopen(nome_ficheiro, "wb");
  if (f == NULL) {
    printf("Erro ao abrir o ficheiro %s\n", nome_ficheiro);
    return 0.0f;
  }

  int totalDownloads = 0, nMusicas = 0;

  for (int i = 0; i < n; i++) {
    if (lista[i].ano > ano) {
      if (((tipo_medio == 's' || tipo_medio == 'a') && lista[i].single) ||
          ((tipo_medio == 'n' || tipo_medio == 'a') && !lista[i].single)) {
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
  // a
  int n = read_int("Qual é o número de musicas?\n");

  MUSIC *musicas = (MUSIC *)malloc(n * sizeof(MUSIC));

  for (int i = 0; i < n; i++) {
    read_music(musicas + i);
  }

  // b
  int nDownloads = read_int("Qual é o minimo de downloads?\n");

  musicas_download(musicas, n, nDownloads);

  // c;
  char interprete[STRING_LENGTH];
  read_string(interprete, "Qual é o nome do intérprete?\n");

  printf("Há %d musicas com o interprete %s.\n", quantidade_de_interprete(musicas, n, interprete), interprete);

  // d
  int ano = read_int("Qual é o ano?\n");

  char single;

  do {
    single = read_char("Singles (s), não singles (n), ou ambos (a)?");
  } while (single != 's' && single != 'n' && single != 'a');

  printf("Número médio de downloads: %.2f", grava_ficheiro_musicas(musicas, n, ano, FICHEIRO_MUSICAS, single));
}
