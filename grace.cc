#include <iostream>

#include "grace/frontend/lexer.h"

namespace frontend = grace::frontend;

int main() {
  const char *source = "   23.44 * / 1 + 1+ 1.11";
  frontend::Lexer lexer = frontend::Lexer(source);

  while (true) {
    frontend::Token token = lexer.next();
    std::cout << token.toString() << "\n";
    if (lexer.eof()) {
      token = lexer.next();
      std::cout << token.toString() << "\n";
      break;
    }
  }
  std::cout << "[END]" << std::endl;
  return 0;
}
