#include "tree.h"

#include "../util/util.c"

TREE *criar_arvore() {
  TREE *arvore = (TREE *)malloc(sizeof(TREE));
  if (!arvore) return NULL;

  arvore->root = NULL;
  arvore->size = 0;

  return arvore;
}

NODE *criar_no() {
  NODE *no = (NODE *)malloc(sizeof(NODE));
  if (!no) return NULL;

  no->info = (PESSOA *)malloc(sizeof(PESSOA));
  if (!no->info) {
    free(no);
    return NULL;
  }

  no->left = no->right = NULL;

  return no;
}

void ler_no(NODE *no) {
  if (!no) return;

  read_string(no->info->nome, "Introduza o seu nome: ");
  no->info->idade = read_int("Introduza a sua idade: ");
  no->info->peso = read_int("Introduza o seu peso: ");
}

int comparar_nos(NODE *A, NODE *B) {
  if (!A || !B) return 0;

  return A->info->idade - B->info->idade;
}

int nos_iguais(NODE *A, NODE *B) {
  return comparar_nos(A, B) == 0;
}

void inserir_no(TREE *tree, NODE *no_novo) {
  if (!no_novo || !tree) return;

  NODE *root = get_node_root(tree->root, no_novo), *tmp;

  if (!root) {
    tree->root = no_novo;
  } else if (comparar_nos(no_novo, root) > 0) {
    if (!root->right) {
      root->right = no_novo;
    } else {
      tmp = root->right;
      root->right = no_novo;
      no_novo->right = tmp;
    }
  } else {
    if (!root->left) {
      root->left = no_novo;
    } else {
      tmp = root->left;
      root->left = no_novo;
      no_novo->left = tmp;
    }
  }

  tree->size++;

  return;
}

NODE *pesquisar(TREE *tree, int idade) {
  if (!tree) return NULL;

  NODE *root = tree->root;
  while (root) {
    if (idade == root->info->idade) return root;
    root = comparar_nos(idade, root) > 0 ? root->right : root->left;
  }

  return NULL;
}

void mostrar_no(NODE *no_mostrar) {
  if (!no_mostrar) return;

  printf("--------- NO ---------\n");
  printf("Nome: %s\n", no_mostrar->info->nome);
  printf("Idade: %d\n", no_mostrar->info->idade);
  printf("Peso: %d\n", no_mostrar->info->peso);
  printf("----------------------\n");
}

void mostrar_in_order(TREE *tree) {
  if (!tree) return;

  NODE *root = tree->root;
  if (!root) return;

  _show_tree_inorder(root);
}

void mostrar_pre_order(TREE *tree) {
  if (!tree) return;

  NODE *root = tree->root;
  if (!root) return;

  _show_tree_preorder(root);
}

void mostrar_post_order(TREE *tree) {
  if (!tree) return;

  NODE *root = tree->root;
  if (!root) return;

  _show_tree_postorder(root);
}

void libertar_no(NODE *no_libertar) {
  if (!no_libertar) return;

  free(no_libertar->info);
  free(no_libertar);
}

NODE *remover(NODE *no_remover, NODE **raiz) {
  if (!no_remover || !raiz) return NULL;

  NODE *root = *raiz;
  if (!root) return NULL;

  if (comparar_nos(no_remover, root) > 0) {
    root->right = remover(no_remover, &root->right);
  } else if (comparar_nos(no_remover, root) < 0) {
    root->left = remover(no_remover, &root->left);
  } else {
    if (!root->left && !root->right) {
      *raiz = NULL;
      libertar_no(root);
      return NULL;
    } else if (!root->left) {
      *raiz = root->right;
      libertar_no(root);
      return root->right;
    } else if (!root->right) {
      *raiz = root->left;
      libertar_no(root);
      return root->left;
    } else {
      NODE *tmp = root->right;
      while (tmp->left) tmp = tmp->left;
      root->info = tmp->info;
      root->right = remover(tmp, &root->right);
    }
  }

  return root;
}

int contar_nos(TREE *tree) {
  if (!tree) return 0;

  return tree->size;
}

int contar_nos_sup_idade(TREE *tree, int idade_min) {
  if (!tree) return 0;

  NODE *root = tree->root;
  if (!root) return 0;

  int amount = 0;
  _count_tree_sup_idade(root, idade_min, &amount);
  return amount;
}

int contar_nos_inf_peso(TREE *tree, float peso_max) {
  if (!tree) return 0;

  NODE *root = tree->root;
  if (!root) return 0;

  int amount = 0;
  _count_tree_inf_peso(root, peso_max, &amount);
  return amount;
}

int altura_arvore(TREE *tree) {
  if (!tree) return 0;

  NODE *root = tree->root;
  if (!root) return 0;

  return _height_tree(root);
}

NODE *get_node_root(NODE *root, NODE *node) {
  if (!root) return NULL;

  int cmp = comparar_nos(node, root);

  if (cmp > 0) {
    root->right = get_node_root(root->right, node);
  } else if (cmp < 0) {
    root->left = get_node_root(root->left, node);
  }

  return root;
}

void _show_tree_preorder(NODE *node) {
  if (!node) return;

  mostrar_no(node);
  show_tree_preorder(node->left);
  show_tree_preorder(node->right);
}

void _show_tree_inorder(NODE *node) {
  if (!node) return;

  show_tree_inorder(node->left);
  mostrar_no(node);
  show_tree_inorder(node->right);
}

void _show_tree_postorder(NODE *node) {
  if (!node) return;

  show_tree_postorder(node->left);
  show_tree_postorder(node->right);
  mostrar_no(node);
}

void _count_tree_sup_idade(NODE *root, int idade_min, int *amount) {
  if (!root) return;

  if (root->info->idade >= idade_min) (*amount)++;

  _count_tree_sup_idade(root->right, idade_min, amount);
  _count_tree_sup_idade(root->left, idade_min, amount);
}

void _count_tree_inf_idade(NODE *root, int idade_min, int *amount) {
  if (!root) return;

  if (root->info->idade <= idade_min) (*amount)++;

  _count_tree_inf_idade(root->right, idade_min, amount);
  _count_tree_inf_idade(root->left, idade_min, amount);
}

int _height_tree(NODE *root) {
  if (!root) return 0;

  int left = _height_tree(root->left);
  int right = _height_tree(root->right);

  return left > right ? left + 1 : right + 1;
}
