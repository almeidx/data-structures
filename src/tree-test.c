#include "util/tree.c"

#define COUNT 2

char *allocate_string(char *str) {
  char *tmp = malloc(sizeof(char) * (strlen(str) + 1));
  strcpy(tmp, str);
  return tmp;
}

void main() {
  TREE *tree = create_tree();

  insert_node(tree, allocate_string("E"));
  insert_node(tree, allocate_string("K"));
  insert_node(tree, allocate_string("D"));
  insert_node(tree, allocate_string("B"));
  insert_node(tree, allocate_string("G"));
  insert_node(tree, allocate_string("A"));
  insert_node(tree, allocate_string("C"));
  insert_node(tree, allocate_string("F"));
  insert_node(tree, allocate_string("Z"));

  printf("show_pre_order: ");
  show_tree_preorder(tree->root);
  printf("\n");

  printf("show_in_order: ");
  show_tree_inorder(tree->root);
  printf("\n");

  printf("show_post_order: ");
  show_tree_postorder(tree->root);
  printf("\n");

  NODE *n = search_node(tree->root, "Z");
  if (n) {
    printf("search_node: %s\n", n->info);
  } else {
    printf("search_node: not found\n");
  }

  printf("Size: %d\n", get_tree_size(tree));

  destroy_tree(tree);
}
