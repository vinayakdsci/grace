#include <gtest/gtest.h>
extern "C" {
#include "src/core/lexer.h"
}

TEST(GraceLexerCorrectnessTests, OneTokenTest) {
  const char *src1 = "1";
  const char *src2 = "1.11";
  const char *src3 = "1.11 + 1";
  const char *src4 = "1.11 + -1";
  const char *src5 = "fn a(5, 3);";

  const token_type_t result_tts_src5[] = {
      TOKEN_FN,    TOKEN_IDENT,  TOKEN_LPAREN, TOKEN_NUMBER,
      TOKEN_COMMA, TOKEN_NUMBER, TOKEN_RPAREN, TOKEN_SEMICOLON,
  };

  const char *literals5[] = {
      "fn", "a", "(", "5", ",", "3", ")", ";",
  };

  lexer_t *l1 = init_lexer(src1);
  lexer_t *l2 = init_lexer(src2);
  lexer_t *l3 = init_lexer(src3);
  lexer_t *l4 = init_lexer(src4);
  lexer_t *l5 = init_lexer(src5);

  token_t *t1 = lex_next_token(&l1);
  token_t *t2 = lex_next_token(&l2);
  token_t *t3 = lex_next_token(&l3);
  token_t *t4 = lex_next_token(&l4);

  ASSERT_TRUE(t1->token_type_ == TOKEN_NUMBER);
  ASSERT_TRUE(!strcmp(t1->token_literal_, "1"));

  ASSERT_TRUE((t2->token_type_ == TOKEN_NUMBER) &&
              (!strcmp(t2->token_literal_, "1.11")));

  ASSERT_TRUE((t3->token_type_ == TOKEN_NUMBER) &&
              (!strcmp(t3->token_literal_, "1.11")));
  free_token(&t3);

  t3 = lex_next_token(&l3);
  ASSERT_TRUE((t3->token_type_ == TOKEN_PLUS) &&
              (!strcmp(t3->token_literal_, "+")));
  free_token(&t3);

  t3 = lex_next_token(&l3);
  ASSERT_TRUE((t3->token_type_ == TOKEN_NUMBER) &&
              (!strcmp(t3->token_literal_, "1")));
  free_token(&t3);

  int counter = 0;
  while (1) {
    token_t *t = lex_next_token(&l5);
    if (t->token_type_ == TOKEN_EOF) {
      break;
    }
    EXPECT_TRUE((!strcmp(t->token_literal_, literals5[counter])) &&
                t->token_type_ == result_tts_src5[counter])
        << t->token_literal_ << " " << counter;
    counter++;
    free_token(&t);
  }

  free_token(&t1);
  free_token(&t2);
  free_token(&t4);

  free_lexer(&l1);
  free_lexer(&l2);
  free_lexer(&l3);
  free_lexer(&l4);
  free_lexer(&l5);
}
