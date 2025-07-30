// Copyright 2025 Vinayak Dev
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GRACE_PARSER_H_
#define GRACE_PARSER_H_

#include "grace/frontend/ast.h"
#include "grace/frontend/lexer.h"

namespace grace {
namespace frontend {

class Parser {
private:
  Lexer lexer_;
  Token current_;
  Token previous_;
  void advance();
  bool check(TokenType tt);
  int getCurrentTokenPrecedence();

  template <TokenType T, TokenType... Ts> void expect(const char *err);

  template <TokenType T, TokenType... Ts> bool match();

  std::unique_ptr<Expression> parseExpression();
  std::unique_ptr<Expression> parseUnary();
  std::unique_ptr<Expression> parsePrimary();
  std::unique_ptr<Expression> parseBinary(int exprPrecedence,
                                          std::unique_ptr<Expression> lhs);

  std::unordered_map<TokenType, int> precedence_ = {
      {TokenType::Plus, 20},
      {TokenType::Minus, 20},
      {TokenType::Star, 40},
      {TokenType::Slash, 40},
  };
};

} // namespace frontend
} // namespace grace

#endif
