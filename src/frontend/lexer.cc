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
#include "grace/frontend/lexer.h"
#include "grace/utils/string_utils.h"
#include <llvm/Support/ErrorHandling.h>
#include <llvm/Support/raw_ostream.h>
#include <string>

namespace grace {
namespace frontend {

Token Lexer::lexNumber() {
  bool isFloat = false;
  while (utils::isDigit(peek())) {
    advance();
  }

  if (peek() == '.' && utils::isDigit(peekNext())) {
    isFloat = true;
    // Consume the '.'
    advance();
    while (utils::isDigit(peek())) {
      advance();
    }
  }

  std::string s = "";
  int64_t len = static_cast<int64_t>(offset_ - start_);
  s.reserve(len);

  for (int64_t i = 0; i < len; ++i) {
    s.push_back(start_[i]);
  }

  if (isFloat) {
    double floatValue = std::stod(s);
    return Token(TokenType::Constant, floatValue);
  }

  long long intValue = std::stoll(s);
  return Token(TokenType::Constant, intValue);
}

Token Lexer::next() {
  if (eof()) {
    return Token(TokenType::Eof);
  }

  start_ = offset_;
  curr_ = advance();

  // Whitespaces/Newlines should be skipped.
  while (utils::isAsciiWhitespace(curr_)) {
    curr_ = advance();
  }

  switch (curr_) {
  case '+':
    return Token(TokenType::Plus);
  case '-':
    return Token(TokenType::Minus);
  case '*':
    return Token(TokenType::Star);
  case '/':
    return Token(TokenType::Slash);
  default:
    if (utils::isDigit(curr_)) {
      return lexNumber();
    }

    std::string msg = "Unsupported token encountered:" + std::string{curr_};
    llvm_unreachable(msg.c_str());
  }
}

} // namespace frontend
} // namespace grace
