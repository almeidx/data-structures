#include "queue.h"

#include "vehicle.c"

QUEUE *create_queue() {
  QUEUE *queue = (QUEUE *)malloc(sizeof(QUEUE));
  if (!queue) return NULL;

  queue->head = queue->tail = NULL;
  queue->size = 0;

  return queue;
}

/*
  5. Escreva uma função que liste todas as viaturas em espera, mostrando os seus dados.
*/
void show_queue(QUEUE *queue) {
  if (!queue) return;

  if (!queue->size) {
    printf("A fila esta vazia.\n");
    return;
  }

  printf("---- Fila ----\n");

  NODE *current = queue->head;
  while (current) {
    show_vehicle(current->vehicle);
    current = current->next;
  }
}

/*
  7. Escreva uma função que permita saber quantas viaturas estão ainda à espera da lavagem.
*/
int get_queue_size(QUEUE *queue) {
  if (!queue) return -1;
  return queue->size;
}

/*
  8. Escreva uma função que permita inserir uma viatura na fila de espera.
*/
void enqueue(QUEUE *queue, VEHICLE *vehicle) {
  NODE *node = (NODE *)malloc(sizeof(NODE));
  if (!node) return;

  node->vehicle = vehicle;
  node->next = NULL;

  if (!queue->head) {
    queue->head = queue->tail = node;
  } else {
    queue->tail->next = node;
    queue->tail = node;
  }

  queue->size++;
}

/*
  9. Escreva uma função que permita retirar uma viatura da fila de espera, mas que antes preencha o tempo de saída e
  calcule o tempo de lavagem para mostrar ao utilizador.
*/
VEHICLE *dequeue(QUEUE *queue, VEHICLE *vehicle) {
  if (!queue || !queue->head) return NULL;

  NODE *current = queue->head;
  while (current) {
    if (compare_vehicles(current->vehicle, vehicle)) {
      vehicle->left_at = time(NULL);
      vehicle->wash_time = get_wash_time(vehicle);
      break;
    }
    current = current->next;
  }

  if (!current) return NULL;

  if (compare_vehicles(queue->head->vehicle, queue->tail->vehicle)) {
    queue->head = queue->tail = NULL;
  } else {
    queue->head = queue->head->next;
  }

  queue->size--;

  return current->vehicle;
}

/*
  10. Elabore uma função que grave os dados das viaturas na fila num ficheiro “fila.dat”.
*/
void save_queue_to_file(QUEUE *queue) {
  FILE *f = fopen(QUEUE_DAT_FILENAME, "wb");
  if (!f) return;

  NODE *current = queue->head;
  while (current) {
    fwrite(current->vehicle, sizeof(VEHICLE), 1, f);
    current = current->next;
  }

  fclose(f);
}

/*
  11. Elabore uma função que permita ler os dados no ficheiro “fila.dat” e adicione as respetivas viaturas à fila de
  espera.
*/
void load_queue_from_file(QUEUE *queue) {
  FILE *f = fopen(QUEUE_DAT_FILENAME, "rb");
  if (!f) return;

  VEHICLE *vehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
  while (fread(vehicle, sizeof(VEHICLE), 1, f)) {
    enqueue(queue, vehicle);
  }

  fclose(f);
}

void remove_all_vehicles(QUEUE *queue) {
  if (!queue) return;

  NODE *current = queue->head;
  while (current) {
    NODE *next = current->next;
    free(current->vehicle);
    free(current);
    current = next;
  }

  queue->head = queue->tail = NULL;
  queue->size = 0;
}

/*
  12. Elabore uma função que permita limpar a fila (eliminar todas as viaturas existentes).
*/
void destroy_queue(QUEUE *queue) {
  if (!queue) return;

  NODE *current = queue->head, *next = NULL;
  while (current) {
    next = current->next;
    destroy_vehicle(current->vehicle);
    free(current);
    current = next;
  }

  free(queue);
}

VEHICLE *find_vehicle_by_plate(QUEUE *queue, char *plate) {
  if (!queue) return NULL;

  NODE *current = queue->head;
  while (current) {
    if (!strcmp(current->vehicle->plate, plate)) {
      return current->vehicle;
    }

    current = current->next;
  }

  return NULL;
}

void wait_for_continue() {
  flush_stdin();

  printf("\n\nPress ENTER to continue...");
  getchar();
}

/*
  13. Escreva uma função MENU() que oriente o utilizador do programa na escolha das diferentes funcionalidades que lhe
  são proporcionadas.

  Retorna 1 se o utilizador quiser sair, caso contrario retorna 0
*/
int menu(QUEUE *queue) {
  int option;

  do {
    flush_stdin();

    printf(
        "(1) Inserir viatura\n"
        "(2) Remover viatura\n"
        "(3) Mostrar viaturas em espera\n"
        "(4) Remover todas as viaturas\n"
        "(5) Exportar fila para ficheiro\n"
        "(6) Importar fila de um ficheiro\n"
        "(0) SAIR\n");

    scanf("%d", &option);
  } while (option < 0 || option > 6);

  switch (option) {
    case 1:
      enqueue(queue, read_vehicle());
      break;

    case 2: {
      char plate[MAX_PLATE];
      read_string(plate, "Insira a matricula do veiculo que quer remover: ");

      VEHICLE *vehicle = find_vehicle_by_plate(queue, plate);
      if (!vehicle) {
        printf("Nao existe nenhum veiculo com a matricula %s.\n", plate);
        break;
      }

      vehicle = dequeue(queue, vehicle);
      printf("O veiculo %s ficou %d segundos a lavar.\n", vehicle->plate, get_wash_time(vehicle));
      break;
    }

    case 3:
      show_queue(queue);
      break;

    case 4:
      remove_all_vehicles(queue);
      break;

    case 5:
      save_queue_to_file(queue);
      break;

    case 6:
      load_queue_from_file(queue);
      break;

    case 0:
      return 1;
  }

  wait_for_continue();

  return 0;
}
