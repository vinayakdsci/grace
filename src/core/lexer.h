#ifndef GRACE_CORE_LEXER_H_
#define GRACE_CORE_LEXER_H_

#include <stdlib.h>

typedef struct lexer_t {
	char *input_;
	char *current_offset_;
	char *read_offset_;
	char current_;
} lexer_t;

lexer_t test_drive();

#endif
