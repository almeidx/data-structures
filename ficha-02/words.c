#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

WORD *create_word(char *text) {
  WORD *word = (WORD *)malloc(sizeof(WORD));
  strcpy(word->text, text);
  return word;
}
