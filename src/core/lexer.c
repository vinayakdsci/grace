#include "lexer.h"

#include <stdbool.h>
#include <string.h>

#include "macros.h"
#include "memory.h"

typedef struct literal_token_tuple {
  char *keyword;
  token_type_t mapped_token;
} token_mapping_t;

// Extend this table when new keywords are added.
static const token_mapping_t keywords[] = {
    {"let", TOKEN_LET},
    {"fn", TOKEN_FN},
};

static size_t keyword_map_size() {
  return sizeof(keywords) / sizeof(keywords[0]);
}

// A bunch of helper functions to help wire up the lexer.
static bool reached_eof(lexer_t **lexer) {
  return *(*lexer)->current_offset_ == '\0';
}

static char advance(lexer_t **lexer) {
  lexer_t *lexer_deref = *lexer;
  lexer_deref->current_offset_++;

  return lexer_deref->current_offset_[-1];
}

static char peek(lexer_t **lexer) {
  lexer_t *lexer_deref = *lexer;
  return *lexer_deref->current_offset_;
}

static char peek_next(lexer_t **lexer) {
  lexer_t *lexer_deref = *lexer;
  if (reached_eof(lexer)) {
    return '\0';
  }
  return lexer_deref->current_offset_[1];
}

static bool match_and_advance(lexer_t **lexer, char c) {
  if (reached_eof(lexer)) {
    return false;
  }
  if (peek(lexer) != c) {
    return false;
  }

  (*lexer)->current_offset_++;
  return true;
}

static bool is_digit(char c) { return c <= '9' && c >= '0'; }

static bool is_alpha(char c) {
  return (c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a');
}

static token_type_t map_ident_to_token_type(const char *literal) {
  size_t iter_bound = keyword_map_size();
  for (size_t i = 0; i < iter_bound; ++i) {
    if (!strcmp(literal, keywords[i].keyword)) {
      return keywords[i].mapped_token;
    }
  }
  return TOKEN_IDENT;
}

static token_t *read_identifier(lexer_t **lexer) {
  while (is_alpha(*(*lexer)->current_offset_) ||
         is_digit(*(*lexer)->current_offset_)) {
    advance(lexer);
  }

  lexer_t *lexer_deref = *lexer;
  const int ident_len =
      (int)(lexer_deref->current_offset_ - lexer_deref->read_offset_) + 1;
  char *literal = ALLOCATE(char, ident_len);

  if (!literal) {
    fprintf(stderr,
            "Could not allocate token literal on heap. System possibly OUT OF "
            "MEMORY.");
    exit(1);
  }

  // We memcpy (ident_len - 1) chars because the last one is reserved for the
  // null byte.
  memcpy(literal, lexer_deref->read_offset_, ident_len - 1);
  literal[ident_len - 1] = '\0';
  lexer_deref->current_ = peek(lexer);
  token_type_t token_type = map_ident_to_token_type(literal);

  // FIXME: Need handling for column and line number for error reporting.
  token_t *token = init_and_set_token(0, 0, token_type, literal);

  return token;
}

static token_t *read_number(lexer_t **lexer) {
  lexer_t *lexer_deref = *lexer;
  while (is_digit(peek(lexer))) {
    advance(lexer);
  }

  if (peek(lexer) == '.' && is_digit(peek_next(lexer))) {
    // Consume the '.'
    advance(lexer);
    while (is_digit(peek(lexer))) {
      advance(lexer);
    }
  }

  const int number_len =
      (int)(lexer_deref->current_offset_ - lexer_deref->read_offset_) + 1;
  char *literal = ALLOCATE(char, number_len);

  if (!literal) {
    fprintf(stderr,
            "Could not allocate token literal on heap. System possibly OUT OF "
            "MEMORY.");
    exit(1);
  }

  // We memcpy (number_len - 1) chars because the last one is reserved for the
  // null byte.
  memcpy(literal, lexer_deref->read_offset_, number_len - 1);
  literal[number_len - 1] = '\0';
  lexer_deref->current_ = peek(lexer);

  // FIXME: Need handling for column and line number for error reporting.
  token_t *token = init_and_set_token(0, 0, TOKEN_NUMBER, literal);

  return token;
}

static void skip_whitespace(lexer_t **lexer) {
  for (;;) {
    char cur = peek(lexer);
    switch (cur) {
      case ' ':
      case '\r':
      case '\t':
        advance(lexer);
        break;
      case '\n':
        // This is where line number should be handled.
        advance(lexer);
        break;
      case '#':
        while (peek(lexer) != '\n' && !reached_eof(lexer)) advance(lexer);
        break;
      default:
        return;
    }
  }
}

lexer_t *init_lexer(const char *source) {
  char *source_ = strdup(source);

  if (!source_) {
    fprintf(
        stderr,
        "Could not copy source string to heap. System possibly OUT OF MEMORY.");
    exit(1);
  }

  lexer_t *lexer = ALLOCATE(lexer_t, 1);
  lexer->source_ = source_;
  lexer->current_ = source_[0];
  lexer->read_offset_ = source_;
  lexer->current_offset_ = source_;

  return lexer;
}

token_t *lex_next_token(lexer_t **lexer_ptr) {
  skip_whitespace(lexer_ptr);
  lexer_t *lexer_deref = *lexer_ptr;

  lexer_deref->read_offset_ = lexer_deref->current_offset_;
  if (reached_eof(lexer_ptr)) {
    return init_and_set_token(0, 0, TOKEN_EOF, "EOF");
  }

  char curr = advance(lexer_ptr);
  switch (curr) {
    case '+':
      return init_and_set_token(0, 0, TOKEN_PLUS, "+");
    case '-':
      return init_and_set_token(0, 0, TOKEN_MINUS, "-");
    case '/':
      return init_and_set_token(0, 0, TOKEN_SLASH, "/");
    case '*':
      return init_and_set_token(0, 0, TOKEN_STAR, "*");
    case '(':
      return init_and_set_token(0, 0, TOKEN_LPAREN, "(");
    case ')':
      return init_and_set_token(0, 0, TOKEN_RPAREN, ")");
    case ',':
      return init_and_set_token(0, 0, TOKEN_COMMA, ",");
    case ';':
      return init_and_set_token(0, 0, TOKEN_SEMICOLON, ";");
    default: {
      if (is_alpha(curr)) {
        return read_identifier(lexer_ptr);
      }
      if (is_digit(curr)) {
        return read_number(lexer_ptr);
      }
      char illegal[] = {curr};
      fprintf(stderr,
              "[WARNING] Encountered illegal token in input stream: %c\n",
              curr);
      return init_and_set_token(0, 0, TOKEN_ERROR, illegal);
    }
  }
}
void free_lexer(lexer_t **lexer_ptr) {
  GRACE_ASSERT((*lexer_ptr)->source_,
               "Cannot free lexer's source pointer as it is NULL");

  free((*lexer_ptr)->source_);
  (*lexer_ptr)->source_ = NULL;

  free(*lexer_ptr);
  *lexer_ptr = NULL;
}
