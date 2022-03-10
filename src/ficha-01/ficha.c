#include "../util/util.c"
#include "./data.h"

/*
  Implemente as seguintes funcionalidades, criando as funções com o nome indicado:

  Parte 1:
    1. LerFicheiro; // Deve ler os dados do ficheiro
    2. OrdenarDados; // Deve implementar um método de ordenação
    3. LibertarMemoria; // Deve libertar toda a memória alocada
    4. ListarUtilizadores; // Deve Listar todos os utilizadores
    5. Criar um programa principal, de modo a poder chamar todas as funções desenvolvidas nas questões 1 a 4.

  Parte 2:
    6. Contar o número de pessoas que fizeram o último acesso ao site num dado ano (função: ContarPessoasAcessosAno);
    7. Pesquisar pelo código (função: PesquisarCod);
    8. Pesquisar pelo nome (função: PesquisarNome);
    9. Determinar a pessoa que fez mais acessos (função: PessoaMais_Acessos);
    10. Determinar a soma de todas as “joias” (função: TotalJoias);
    11. Determinar qual o mês em que houve mais acessos (função MesMaisAcessos);
    12. Alterar o programa principal de modo a poder invocar as novas funcionalidades desenvolvidas.
*/

/*
  a) Como perceberam, o fich. *)"Utilizadores.dat” não foi fornecido. Mas, pretendem resolver o problema e poderem
  executar as opções da aplicação….
  Sugestão: Implementar uma função para gerar aleatoriamente muitos dados REGISTO_UTILIZADORES e gravar no ficheiro
  “Utilizadores.dat”. Por exemplo, uma função com o seguinte protótipo:
    void GerarFicheiro_So_Para_Testes(char *nficheiro);
*/
void generate_test_file(int n_utilizadores) {
  FILE *f = open_file(FICHEIRO_UTILIZADORES, "wb");

  for (int i = 0; i < n_utilizadores; i++) {
    REGISTO_UTILIZADORES utilizador;

    rand_str(utilizador.nome, 50);
    rand_str(utilizador.utilizador, 20);
    rand_str(utilizador.password, 20);
    utilizador.joia = (float)rand() / RAND_MAX * 100.0f;
    rand_date(utilizador.data_registo);
    rand_str(utilizador.email, 30);
    rand_str(utilizador.pagina_web_pessoal, 50);
    utilizador.telemovel = rand() % 9999999999 + 1;
    utilizador.numero_acessos = rand() % 100 + 1;
    rand_date(utilizador.data_ultimo_acesso);

    fwrite(&utilizador, sizeof(REGISTO_UTILIZADORES), 1, f);
  }

  fclose(f);
}

// 1.
void ler_ficheiro(REGISTO_UTILIZADORES *utilizadores, int n_utilizadores) {
  FILE *f = open_file(FICHEIRO_UTILIZADORES, "rb");

  for (int i = 0; i < n_utilizadores; i++) {
    fread(&utilizadores[i], sizeof(REGISTO_UTILIZADORES), 1, f);
  }

  fclose(f);
}

// 2.
void ordenar_dados(REGISTO_UTILIZADORES *utilizadores, int n_utilizadores, char sorting_order) {
  for (int i = 0; i < n_utilizadores; i++) {
    for (int j = 0; j < n_utilizadores - 1; j++) {
      if (sorting_order == 'a') {
        if (utilizadores[j].joia < utilizadores[j + 1].joia) {
          REGISTO_UTILIZADORES aux = utilizadores[j];
          utilizadores[j] = utilizadores[j + 1];
          utilizadores[j + 1] = aux;
        }
      } else {
        if (utilizadores[j].joia > utilizadores[j + 1].joia) {
          REGISTO_UTILIZADORES aux = utilizadores[j];
          utilizadores[j] = utilizadores[j + 1];
          utilizadores[j + 1] = aux;
        }
      }
    }
  }
}

// 4.
void listar_utilizadores(REGISTO_UTILIZADORES *utilizadores, int n_utilizadores) {
  for (int i = 0; i < n_utilizadores; i++) {
    printf("%d. %s\n", i + 1, utilizadores[i].utilizador);
  }
}

// 6.
int numero_de_acessos_no_ano(REGISTO_UTILIZADORES *utilizadores, int n_utilizadores, int ano_minimo) {
  int num_acessos = 0;

  for (int i = 0; i < n_utilizadores; i++) {
    if (utilizadores[i].data_ultimo_acesso.ano >= ano_minimo) {
      num_acessos++;
    }
  }

  return num_acessos;
}

// 8.
REGISTO_UTILIZADORES pesquisar_nome(REGISTO_UTILIZADORES *utilizadores, int n_utilizadores, char *nome) {
  for (int i = 0; i < n_utilizadores; i++) {
    if (!strcmp(utilizadores[i].nome, nome)) {
      return utilizadores[i];
    }
  }
}

// 9.
REGISTO_UTILIZADORES utilizador_mais_acessos(REGISTO_UTILIZADORES *utilizadores, int n_utilizadores) {
  REGISTO_UTILIZADORES utilizador_mais_acessos = utilizadores[0];

  for (int i = 0; i < n_utilizadores; i++) {
    if (utilizador_mais_acessos.numero_acessos < utilizadores[i].numero_acessos) {
      utilizador_mais_acessos = utilizadores[i];
    }
  }

  return utilizador_mais_acessos;
}

// 10.
float total_joias(REGISTO_UTILIZADORES *utilizadores, int n_utilizadores) {
  float total = 0.0f;

  for (int i = 0; i < n_utilizadores; i++) {
    total += utilizadores[i].joia;
  }

  return total;
}

// 11.
int mes_mais_acessos(REGISTO_UTILIZADORES *utilizadores, int n_utilizadores) {
  int mes_mais_acessos = 0, num_acessos = 0;

  for (int i = 0; i < n_utilizadores; i++) {
    if (utilizadores[i].numero_acessos > num_acessos) {
      mes_mais_acessos = utilizadores[i].data_ultimo_acesso.mes;
      num_acessos = utilizadores[i].numero_acessos;
    }
  }

  return mes_mais_acessos;
}

void main() {
  // 1.
  int n_utilizadores = read_int("Número de utilizadores: ");
  REGISTO_UTILIZADORES *utilizadores = malloc(sizeof(REGISTO_UTILIZADORES) * n_utilizadores);

  generate_test_file(n_utilizadores);

  ler_ficheiro(utilizadores, n_utilizadores);

  // 2.
  char sorting_order;
  do {
    sorting_order = read_char("Ordenar por ordem crescente (a) ou decrescente (d)? ");
  } while (sorting_order != 'a' && sorting_order != 'd');

  ordenar_dados(utilizadores, n_utilizadores, sorting_order);

  // 4.
  listar_utilizadores(utilizadores, n_utilizadores);

  // 6.
  int ano_minimo = read_int("Ano mínimo: ");
  numero_de_acessos_no_ano(utilizadores, n_utilizadores, ano_minimo);

  // 8.
  char nome[STRING_LENGTH];
  read_string(nome, "Nome do utilizador que quer pesquisar: ");

  REGISTO_UTILIZADORES utilizador = pesquisar_nome(utilizadores, n_utilizadores, nome);

  printf("Utilizador: %s\n.", utilizador.utilizador);

  // 9.
  REGISTO_UTILIZADORES _utilizador_mais_acessos = utilizador_mais_acessos(utilizadores, n_utilizadores);
  printf("O utilizador com mais acessos é '%s' e com %d acessos.\n", _utilizador_mais_acessos.utilizador,
         _utilizador_mais_acessos.numero_acessos);

  // 10.
  printf("O total de joias é %.2f.\n", total_joias(utilizadores, n_utilizadores));

  // 11.
  printf("O mês com mais acessos é %d.\n", mes_mais_acessos(utilizadores, n_utilizadores));

  free(utilizadores);
}
