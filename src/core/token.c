#include "token.h"

#include <string.h>

#include "memory.h"

token_t *init_token() {
  token_t *new_token = ALLOCATE(token_t, 1);
  new_token->col_ = 0;
  new_token->line_ = 1;
  new_token->token_type_ = TOKEN_EOF;
  new_token->token_literal_ = NULL;

  return new_token;
}

void set_token_attrs(token_t *token_ptr, unsigned int col,
                     unsigned long long line, token_type_t token_type,
                     const char *token_literal) {
  token_ptr->col_ = col;
  token_ptr->token_literal_ = strdup(token_literal);

  if (!token_ptr->token_literal_) {
    fprintf(
        stderr,
        "Could not copy token literal to heap. System possibly OUT OF MEMORY.");
    exit(1);
  }

  token_ptr->token_type_ = token_type;
  token_ptr->line_ = line;
}

void free_token(token_t **token_ptr) {
  if ((*token_ptr)->token_literal_ != NULL) {
    free((*token_ptr)->token_literal_);
    (*token_ptr)->token_literal_ = NULL;
  }
  free(*token_ptr);
  *token_ptr = NULL;
}
