#include "lexer.h"


lexer_t test_drive() {
	lexer_t lexer =  {
		.input_ = NULL,
		.current_offset_ = NULL,
		.read_offset_ = NULL,
		.current_ = '\0',
	};

	return lexer;
}
