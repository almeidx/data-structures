#include "../util/util.c"

/*
  4. Pretende-se efetuar um estudo sobre a saúde de um determinado número de indivíduos, num dado ano. Para cada
  indivíduo, regista-se o seu número do Cartão de Cidadão, a sua altura, a sua massa, o género (M/F) e a data de
  nascimento (dia, mês, ano).
  Obs. 1. n, em todos os cabeçalhos das funções, representa o número de indivíduos no vetor lista;
       2. utilize ponteiros em todas as alíneas para aceder ao valor dos atributos dos elementos do vetor.
*/

/*
  a) Defina o tipo de dados Indiv, Data e crie um vetor de nome ListIndiv para guardar a informação necessária para este
  estudo, supondo que se pretendem guardar nReg elementos, sendo nReg especificado pelo utilizador;
*/
typedef struct Individuo {
  char cc[STRING_LENGTH];
  float altura, massa;
  /* M/F */
  char genero;
  DATA data_nascimento;
} INDIVIDUO;

/*
  b) Para cada indivíduo calcula-se o Índice de Massa Corporal (IMC) como IMC = massa / altura^2. Considera-se que um
  indivíduo é saudável, se o seu IMC estiver compreendido entre 18,5 e 24,9. Defina a função indSaudaveis que recebe a
  lista de indivíduos e calcula e devolve quantos indivíduos são saudáveis.
*/
int individuos_saudaveis(INDIVIDUO *lista, int n) {
  int saudaveis = 0;
  for (int i = 0; i < n; i++) {
    float imc = lista[i].massa / (lista[i].altura * lista[i].altura);
    if (imc >= 18.5 && imc <= 24.9) {
      saudaveis++;
    }
  }
  return saudaveis;
}

/*
  c) Determine a média da massa corporal dos indivíduos nascidos entre dois anos especificados como parâmetros.
*/
float media_massa_corporal(INDIVIDUO *lista, int n, int ano_inicio, int ano_fim) {
  float soma = 0;
  int n_saudaveis = 0;
  for (int i = 0; i < n; i++) {
    if (lista[i].data_nascimento.ano >= ano_inicio && lista[i].data_nascimento.ano <= ano_fim) {
      soma += lista[i].massa;
      n_saudaveis++;
    }
  }
  return soma / n_saudaveis;
}

/*
  d) Elabore uma função que permita remover do vetor um determinado indivíduo, devendo o vetor ficar ajustado, ou seja,
  não conter elementos vazios.
  void removeIndiv(Indiv *vet_ind, int n, int nCC)
*/
void remove_individuo(INDIVIDUO *lista, int n, char *cc) {
  for (int i = 0; i < n; i++) {
    if (!strcmp(lista[i].cc, cc)) {
      for (int j = i; j < n - 1; j++) {
        lista[j] = lista[j + 1];
      }
      break;
    }
  }
}

void main() {
  // a
  int n = read_int("Número de indivíduos: ");
  INDIVIDUO *lista = (INDIVIDUO *)malloc(n * sizeof(INDIVIDUO));

  // b
  printf("%d indivíduos saudáveis\n", individuos_saudaveis(lista, n));

  // c
  int ano_inicio, ano_fim;
  printf("Introduza o intervalo de anos (início, fim): ");
  scanf("%d %d", &ano_inicio, &ano_fim);

  printf("Média da massa corporal dos indivíduos nascidos entre %d e %d: %.2f\n",
         media_massa_corporal(lista, n, ano_inicio, ano_fim));

  // d
  char cc[STRING_LENGTH];
  readString(cc, "Introduza o número do Cartão de Cidadão do indivíduo a remover: ");

  remove_individuo(lista, n, cc);
}
