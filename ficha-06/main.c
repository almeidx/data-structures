#include "hashing.c"

/*
  25. Escreva uma função int menu_principal() que permita ao utilizador escolher entre as diversas funcionalidades do
  programa.
    (1) Inserir um novo elemento no vector de hashing
    (2) Retirar um elemento do vector de hashing
    (3) Mostrar os elementos do vector de hashing
    (4) Pesquisar um elemento no vector de hashing
    (0) SAIR
*/
char menu_principal();

/*
  26. Escreva a função principal void main() de modo a integrar as funções elaboradas anteriormente.
*/
void main() {
  ELEMENTO *ele_criar, *ele_remover, *ele_pesquisar;

  HASHING *pessoas = criar_vetor_hashing();
  inicializar_vetor_hashing(pessoas);

  for (;;) {
    switch (menu_principal()) {
      case '1':
        ele_criar = criar_elemento();
        ler_elemento(ele_criar);
        inserir_elemento_hashing(pessoas, ele_criar);
        break;

      case '2':
        ele_remover = criar_elemento();
        ele_pesquisar->pessoa->idade = read_int("Idade: ");
        ele_remover = remover_elemento_hashing(pessoas, ele_remover);

        if (ele_remover) {
          printf("O elemento foi removido!\n");
          mostrar_elemento(ele_remover);
          libertar_elemento(ele_remover);
        } else {
          printf("Não foi encontrado nenhum elemento!\n");
        }

        break;

      case '3':
        mostrar_elementos_hashing(pessoas);
        break;

      case '4':
        ele_pesquisar = criar_elemento();
        ele_pesquisar->pessoa->idade = read_int("Idade: ");
        ele_pesquisar = pesquisar_elemento_hashing(pessoas, ele_pesquisar);

        if (ele_pesquisar) {
          printf("Foi encontrado um elemento!\n");
          mostrar_elemento(ele_pesquisar);
        } else {
          printf("Não foi encontrado nenhum elemento!\n");
        }

        break;

      case '0':
        exit(0);
    }
  }
}

char menu_principal() {
  char x;

  printf("\n# MENU PRINCIPAL --------------------------------------------#");
  printf("\n|  (1) Inserir um novo elemento no vector de hashing         |");
  printf("\n|  (2) Retirar um elemento do vector de hashing              |");
  printf("\n|  (3) Mostrar os elementos do vector de hashing             |");
  printf("\n|  (4) Pesquisar um elemento no vector de hashing            |");
  printf("\n|  ----------------------------------------------------------|");
  printf("\n|  (0) SAIR                                                   |");
  printf("\n#------------------------------------------------------------#\n");

  fflush(stdin);

  do {
    printf("\n  Qual a sua opcao ? ");
    fflush(stdin);
    x = getchar();
  } while (x < '0' || x > '4');

  return x;
}
