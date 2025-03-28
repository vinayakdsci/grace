#include <gtest/gtest.h>
extern "C" {
#include <string.h>

#include "src/core/lexer.h"
}

TEST(GraceLexerMemoryTests, AllocateAndFreeToken) {
  token_t *token = init_token();

  ASSERT_TRUE(token != NULL);
  ASSERT_FALSE(token->token_literal_ != NULL);

  set_token_attrs(token, 0, 0, TOKEN_EOF, "EOF");
  ASSERT_TRUE(token->token_literal_ != NULL);

  free_token(&token);
  ASSERT_TRUE(token == NULL);

  token_t *tok = init_and_set_token(0, 0, TOKEN_EOF, "EOF");
  ASSERT_TRUE(!strcmp(tok->token_literal_, "EOF"));

  free_token(&tok);
}

TEST(GraceLexerMemoryTests, AllocateAndFreeLexer) {
  const char *src = "fn main() { return 0; }";

  lexer_t *lexer = init_lexer(src);

  ASSERT_TRUE(lexer != NULL);
  ASSERT_TRUE(lexer->source_ != NULL && !strcmp(lexer->source_, src));
  ASSERT_TRUE(lexer->current_offset_ != NULL &&
              !strcmp(lexer->current_offset_, src));
  ASSERT_TRUE(lexer->read_offset_ != NULL && !strcmp(lexer->read_offset_, src));
  ASSERT_TRUE(lexer->current_ == 'f');

  free_lexer(&lexer);

  ASSERT_TRUE(lexer == NULL);
}
