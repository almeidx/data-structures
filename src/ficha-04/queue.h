#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "vehicle.h"

#define QUEUE_DAT_FILENAME "queue.dat"

/*
  2. Defina estruturas de dados adequadas para manter em memória uma fila de viaturas.
*/
typedef struct Node {
  VEHICLE *vehicle;
  struct Node *next;
} NODE;

typedef struct Queue {
  NODE *head, *tail;
  int size;
} QUEUE;

QUEUE *create_queue();

void enqueue(QUEUE *queue, VEHICLE *vehicle);
VEHICLE *dequeue(QUEUE *queue, VEHICLE *vehicle);

int get_queue_size(QUEUE *queue);

void show_queue(QUEUE *queue);
void destroy_queue(QUEUE *queue);

void save_queue_to_file(QUEUE *queue);
void load_queue_from_file(QUEUE *queue);

int menu();

#endif  // QUEUE_H_INCLUDED
