#ifndef GRACE_CORE_TOKEN_H_
#define GRACE_CORE_TOKEN_H_

#include <stdlib.h>

typedef enum token_type_t {
  // Binary operations.
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,

  // Words.
  TOKEN_NUMBER,
  TOKEN_IDENT,

  // Punctuation.
  TOKEN_SEMICOLON,
  TOKEN_COMMA,
  TOKEN_LPAREN,
  TOKEN_RPAREN,

  // Special tokens.
  TOKEN_EOF,
  TOKEN_ERROR,
} token_type_t;

typedef struct token_t {
  token_type_t token_type_;
  char *token_literal_;
  unsigned long long line_;
  unsigned int col_;
} token_t;

token_t *init_token();
void free_token(token_t **token_ptr);
void set_token_attrs(token_t *token_ptr, unsigned int col,
                     unsigned long long line, token_type_t token_type,
                     const char *token_literal);
#endif
