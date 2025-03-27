#include "lexer.h"

#include <string.h>

#include "macros.h"
#include "memory.h"

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

void free_lexer(lexer_t **lexer_ptr) {
  GRACE_ASSERT((*lexer_ptr)->source_,
               "Cannot free lexer's source pointer as it is NULL");

  free((*lexer_ptr)->source_);
  (*lexer_ptr)->source_ = NULL;

  free(*lexer_ptr);
  *lexer_ptr = NULL;
}
