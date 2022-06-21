#include "../util/util.c"

#define MAX_UCS 5

/*
  3. Pretende-se efetuar um estudo sobre os resultados de avaliação de um determinado número de alunos. Para cada aluno,
  regista-se o seu número mecanográfico, o seu nome e os resultados de avaliação de 5 UCs. Cada UC caracteriza-se pelo
  nome e respetiva avaliação.

  Obs: 1. n, em todos os cabeçalhos das funções, representa o número de alunos no vetor lista;
       2. utilize ponteiros em todas as alíneas para aceder ao valor dos atributos dos elementos do vetor.
 */

/*
  a) Defina o tipo de dados Aluno, UC e crie um vetor de nome ListAlun para guardar a informação necessária para este
  estudo, supondo que se pretendem guardar nReg elementos, sendo nReg especificado pelo utilizador.
*/
typedef struct UC {
  char nome[STRING_LENGTH];
  short nota;
} UC;

typedef struct Aluno {
  char cc[STRING_LENGTH], nome[STRING_LENGTH];
  UC uc[MAX_UCS];
} ALUNO;

void read_aluno(ALUNO *aluno) {
  printf("CC: ");
  read_string(aluno->cc, STRING_LENGTH);

  printf("Nome: ");
  read_string(aluno->nome, STRING_LENGTH);

  for (int i = 0; i < MAX_UCS; i++) {
    printf("UC %d: ", i + 1);
    read_string(aluno->uc[i].nome, STRING_LENGTH);

    printf("Nota: ");
    scanf("%hd", &aluno->uc[i].nota);

    clear_terminal();
  }
}

/*
  b) Para cada aluno, calcula-se a média das notas. Considera-se que um aluno transita se a média, arredondada à
  unidade, for igual ou superior a 10 valores. Defina a função qtosPassam que recebe a lista de alunos e calcula e
  devolvequantos alunos transitam.
*/
int quantos_passam(ALUNO *lista, int n) {
  int passam = 0;
  for (int i = 0; i < n; i++) {
    int soma = 0;
    for (int j = 0; j < MAX_UCS; j++) {
      soma += lista[i].uc[j].nota;
    }
    soma /= MAX_UCS;
    if (soma >= 10) {
      passam++;
    }
  }
  return passam;
}

/*
  c) Determine o número médio de UCs, com notas inferiores a lim (e.g., 8) valores (considere esta média de UCs, como a
  soma total do número de UCs com classificação inferior a lim, a dividir pelo número de alunos).
*/
float media_ucs_inferiores(ALUNO *lista, int n, int lim) {
  int soma = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < MAX_UCS; j++) {
      if (lista[i].uc[j].nota < lim) {
        soma++;
      }
    }
  }
  return (float)soma / (float)n;
}

/*
  d) Elabore uma função que permita listar, num ficheiro de texto, os alunos com as UCs onde obtiveram (val) ou mais
  valores. No fich., deve haver uma linha com o nome do aluno e depois novas linhas para o nome e nota das UC que
  corresponderem à condição estabelecida. Depois, uma linha tipo “------------” como separador, seguindo-se um novo
  aluno e notas respetivas e assim sucessivamente. void listaNotas(Aluno *lista, int n, int val, char *nomeFich)

  Obs.: Em nomeFich está disponível o nome do ficheiro a usar.
  Obs. Sintaxes: FILE* fopen(const char* fileName, const char* mode);
                 fprintf (const void* ptr, …);
*/
void lista_notas(ALUNO *lista, int n, int val, char *nome_ficheiro) {
  FILE *f = fopen(nome_ficheiro, "w");

  for (int i = 0; i < n; i++) {
    bool wrote_name = false;
    for (int j = 0; j < MAX_UCS; j++) {
      if (lista[i].uc[j].nota >= val) {
        if (!wrote_name) {
          fprintf(f, "%s\n", lista[i].nome);
          wrote_name = true;
        }
        fprintf(f, "%s %d\n", lista[i].uc[j].nome, lista[i].uc[j].nota);
      }
    }
    fprintf(f, "------------\n");
  }

  fclose(f);
}

void main() {
  // a
  int n_alunos = read_int("Quantos registos de alunos pretendem-se guardar?\n");
  ALUNO *lista = (ALUNO *)malloc(sizeof(ALUNO) * n_alunos);

  for (int i = 0; i < n_alunos; i++) {
    read_aluno(&lista[i]);
  }

  // b
  printf("%d alunos transitam.\n", quantos_passam(lista, n_alunos));

  // c
  printf("%f media de ucs inferior a 8.\n", media_ucs_inferiores(lista, n_alunos, 8));

  // d
  char nome_ficheiro[STRING_LENGTH];
  read_string(nome_ficheiro, "Nome do ficheiro para guardar a listagem?\n");

  lista_notas(lista, n_alunos, 8, nome_ficheiro);
}
