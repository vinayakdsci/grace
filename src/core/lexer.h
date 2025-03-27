#ifndef GRACE_CORE_LEXER_H_
#define GRACE_CORE_LEXER_H_

#include <stdlib.h>

#include "token.h"

typedef struct lexer_t {
  // We need to save the source pointer to be able to do pointer arithmetic on
  // offsets. This helps us free the correct memory on heap.
  char *source_;
  char *current_offset_;
  char *read_offset_;
  char current_;
} lexer_t;

lexer_t *init_lexer(const char *source);
token_t *lex_next_token();

void free_lexer(lexer_t **lexer_ptr);

#endif
