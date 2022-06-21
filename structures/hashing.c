#include "hashing.h"

HASHING *create_hashing() {
  HASHING *hashing = (HASHING *)malloc(sizeof(HASHING));
  hashing->capacity = MAX_CAPACITY;

  for (int i = 0; i < hashing->capacity; i++) {
    hashing->array[i] = create_list();
  }

  return hashing;
}

void destroy_string(void *input) {
  char *str = (char *)input;
  free(str);
}

void destroy_hashing(HASHING *hashing) {
  if (!hashing) return;

  for (int i = 0; i < hashing->capacity; i++) {
    destroy_list(hashing->array[i], destroy_string);
  }
}

int add_hashing(HASHING *hashing, char *data) {
  if (!hashing || !data) return FAILURE;

  int index = hash(hashing, data);
  if (index < 0 || index >= hashing->capacity) return FAILURE;

  add_to_list(hashing->array[index], data);

  return SUCCESS;
}

void show_string(void *input) {
  char *str = (char *)input;
  printf("%s; ", str);
}

void show_hashing(HASHING *hashing) {
  for (int i = 0; i < hashing->capacity; i++) {
    printf("%d: ", i);
    show_list(hashing->array[i], show_string);
  }
}

int hash(HASHING *hashing, char *x) {
  if (!hashing || !x) return -1;
  return toupper(x[0]) - 'A';
}

int save_hash_to_file(HASHING *hashing, char *filename) {
  if (!hashing || !filename) return FAILURE;

  FILE *file = fopen(filename, "wb");
  if (!file) return FAILURE;

  fwrite(&hashing->capacity, sizeof(int), 1, file);

  for (int i = 0; i < hashing->capacity; i++) {
    NODE *node = hashing->array[i]->head;

    while (node) {
      char *str = (char *)node->data;

      int length = strlen(str);
      fwrite(&length, sizeof(int), 1, file);
      fwrite(str, sizeof(char), length + 1, file);

      node = node->next;
    }
  }

  fclose(file);
  return SUCCESS;
}
