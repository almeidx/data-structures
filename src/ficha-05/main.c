#include "list.c"

void main() {
  LIST *list = create_list();
  if (!list) {
    printf("fatal: could not create list\n");
    return;
  }

  int res;

  do {
    // clear_terminal();
    res = menu(list);
  } while (res == 0);

  free_list(list);
}
