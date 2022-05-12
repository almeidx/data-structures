#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *INFO;

typedef struct Node {
  INFO info;
  struct Node *left, *right;
} NODE;

typedef struct Tree {
  NODE *root;
  int size;
} TREE;

TREE *create_tree();
NODE *create_node(INFO info);

int insert_node(TREE *tree, INFO info);
NODE *search_node(NODE *node, INFO info);

void show_tree_preorder(NODE *node);
void show_tree_inorder(NODE *node);
void show_tree_postorder(NODE *node);

int get_node_size(NODE *node);
int get_tree_size(TREE *tree);

void destroy_node(NODE *node);
void destroy_tree(TREE *tree);

#endif  // TREE_H_INCLUDED
