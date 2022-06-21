#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.c"

// List of random words:
//  - http://math.oxford.emory.edu/site/math117/probSetAllTogether/words.txt

// 31.
void main() {
  LIST *list = create_list("pt");

  int res;
  do {
    clear_terminal();
    res = menu(list);
  } while (res == 0);

  if (res != 2) {
    free_list(list);
  }
}
