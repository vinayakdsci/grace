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

#ifndef GRACE_INCLUDE_LEXER_H_
#define GRACE_INCLUDE_LEXER_H_

#include "grace/frontend/token.h"

namespace grace {
namespace frontend {
class Lexer {
public:
  Lexer(const char *source)
      : source_(source), line_(1), start_(source), offset_(source) {}
  Lexer(const Lexer &) = delete;
  Lexer &operator=(const Lexer &) = delete;

  Token next();

  const bool eof() const { return *offset_ == '\0'; }

private:
  const char advance() {
    offset_++;
    return offset_[-1];
  }
  const char peek() const {
    if (eof()) {
      return '\0';
    }
    return offset_[0];
  }
  const char peekNext() const {
    if (eof()) {
      return '\0';
    }
    return offset_[1];
  }

  Token lexNumber();

  const char *const source_;
  unsigned int line_;
  const char *start_;
  const char *offset_;
  char curr_;
};
} // namespace frontend
} // namespace grace
#endif
