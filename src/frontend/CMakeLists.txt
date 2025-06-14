# This file is intentionally kept very simple.
# It should grow into something much more complex
# as the project increases in size and complexity.

# Add all the source files here.
set(GRCC_FRONTEND_SRC_FILES
	token.cc
	lexer.cc
)

add_library(grcc_frontend ${GRCC_FRONTEND_SRC_FILES})
target_include_directories(grcc_frontend PUBLIC ../../include/)
