#include "../util/util.h"

#define FICHEIRO_UTILIZADORES "utilizadores.dat"

typedef struct {
  char nome[50];
  char utilizador[20];
  char password[20];
  float joia;
  DATA data_registo;
  char email[30];
  char pagina_web_pessoal[50];
  int telemovel;
  int numero_acessos;
  DATA data_ultimo_acesso;
} REGISTO_UTILIZADORES;
