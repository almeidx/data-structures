#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.c"

// List of random words:
//  - http://math.oxford.emory.edu/site/math117/probSetAllTogether/words.txt

// 29.
void main() {
  LIST *list = create_list("pt");

  int res;
  do {
    res = menu(list);
  } while (res == 0);

  if (res != 2) {
    free_list(list);
  }

  // read_list_from_file(list, "words.txt");

  // show_list(list);

  // NODE *node = create_node();
  // node->word = create_word("TesteAppend");
  // append_to_list(list, node);

  // NODE *node2 = create_node();
  // node2->word = create_word("TestePrepend");
  // prepend_to_list(list, node2);

  // if (!compare_nodes(node, node2)) {
  //   printf("Compare nodes is working\n");
  // }

  // if (compare_nodes(iterative_search(list, node), node)) {
  //   printf("Iterative search is working\n");
  // }
  // if (compare_nodes(recursive_search(list, node, list->head), node)) {
  //   printf("Recursive search is working\n");
  // }

  // NODE *repeated_node = create_node();
  // repeated_node->word = create_word("TesteAppend");
  // append_to_list(list, repeated_node);
  // // show_list(list);

  // printf("Amount of repeated nodes: %d\n", amount_of_repeated_words(list));

  // remove_word(list, "Palavras");
  // // show_list(list);

  // remove_first_word(list);
  // // show_list(list);

  // remove_last_word(list);
  // // show_list(list);

  // show_list_reversed_recursive(list, list->head);

  // show_list_reversed_iterative(list);

  // export_list_to_file(list, "words2.txt");
}
