#include "container.c"
#include "stack.c"

void main() {
  STACK *stack = create_stack();

  CONTAINER *c1 = create_container();

  push_to_stack(stack, c1);

  show_stack(stack, show_container);

  destroy_stack(stack);
}
