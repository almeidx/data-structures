#include "tree.h"

TREE *create_tree() {
  TREE *tree = (TREE *)malloc(sizeof(TREE));
  tree->root = NULL;
  tree->size = 0;
  return tree;
}

NODE *create_node(INFO info) {
  NODE *node = malloc(sizeof(NODE));
  node->info = info;
  node->left = NULL;
  node->right = NULL;
  return node;
}

NODE *get_node_root(NODE *root, NODE *node) {
  if (!root) return NULL;

  int cmp = strcmp(node->info, root->info);

  if (cmp > 0) {
    root->right = get_node_root(root->right, node);
  } else if (cmp < 0) {
    root->left = get_node_root(root->left, node);
  }

  return root;
}

int insert_node(TREE *tree, INFO info) {
  if (!tree) return 0;

  NODE *node = create_node(info), *root = get_node_root(tree->root, node), *tmp;

  if (!root) {
    tree->root = node;
  } else if (strcmp(info, root->info) > 0) {
    if (!root->right) {
      root->right = node;
    } else {
      tmp = root->right;
      root->right = node;
      node->right = tmp;
    }
  } else {
    if (!root->left) {
      root->left = node;
    } else {
      tmp = root->left;
      root->left = node;
      node->left = tmp;
    }
  }

  tree->size++;

  return 1;
}

NODE *search_node(NODE *root, INFO info) {
  if (!root) return NULL;

  int cmp = strcmp(info, root->info);
  if (!cmp) return root;

  return search_node(cmp > 0 ? root->right : root->left, info);
}

void show_tree_preorder(NODE *node) {
  if (!node) return;

  printf("%s ", node->info);
  show_tree_preorder(node->left);
  show_tree_preorder(node->right);
}

void show_tree_inorder(NODE *node) {
  if (!node) return;

  show_tree_inorder(node->left);
  printf("%s ", node->info);
  show_tree_inorder(node->right);
}

void show_tree_postorder(NODE *node) {
  if (!node) return;

  show_tree_postorder(node->left);
  show_tree_postorder(node->right);
  printf("%s ", node->info);
}

int get_node_size(NODE *node) {
  if (!node) return 0;
  return 1 + get_node_size(node->left) + get_node_size(node->right);
}

int get_tree_size(TREE *tree) {
  if (!tree) return 0;
  return get_node_size(tree->root);
}

void destroy_node(NODE *node) {
  if (!node) return;

  destroy_node(node->left);
  destroy_node(node->right);

  free(node->info);
  free(node);
}

void destroy_tree(TREE *tree) {
  if (!tree) return;

  destroy_node(tree->root);
  free(tree);
}
