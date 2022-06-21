#include "queue.c"

void main() {
  QUEUE *queue = create_queue();
  if (!queue) {
    printf("fatal: could not create queue\n");
    return;
  }

  int res;

  do {
    // clear_terminal();
    res = menu(queue);
  } while (res == 0);

  destroy_queue(queue);
}
