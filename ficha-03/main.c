#include <stdio.h>
#include <stdlib.h>

#include "container.c"
#include "stack.c"

// 10.
void main() {
  STACK *stack = create_stack();
  if (!stack) {
    printf("fatal: could not create stack\n");
    return;
  }

  int res;

  do {
    clear_terminal();
    res = menu(stack);
  } while (res == 0);

  destroy_stack(stack);
}
