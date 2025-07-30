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

#include "grace/frontend/parser.h"

namespace {
void throwAndSynchronize() {}
} // namespace

namespace grace {
namespace frontend {

int Parser::getCurrentTokenPrecedence() {
  auto tt = precedence_.find(current_.tokenType());
  if (tt == precedence_.end()) {
    return -1;
  }
  return tt->second;
}

void Parser::advance() {
  previous_ = current_;

  for (;;) {
    current_ = lexer_.next();
    if (current_.tokenType() != TokenType::Error) {
      break;
    }
    // TODO: Implement an Error class and a mechanism
    // to synchronize on parser errors.
    throwAndSynchronize();
  }
}

bool Parser::check(TokenType tt) { return current_.tokenType() == tt; }

template <TokenType T, TokenType... Ts> bool Parser::match() {
  if (!check(T)) {
    if constexpr (sizeof...(Ts) > 0) {
      return match<Ts...>();
    }
    return false;
  }

  advance();
  return true;
}

template <TokenType T, TokenType... Ts> void Parser::expect(const char *err) {
  (void)*err;
  (void)err;
  if (!match<T, Ts...>()) {
    throwAndSynchronize();
  }
}

std::unique_ptr<Expression> Parser::parseExpression() {
  // expression := primary | binary
  auto lhs = parsePrimary();
  if (!lhs) {
    return nullptr;
  }
  return parseBinary(0, std::move(lhs));
}

std::unique_ptr<Expression>
Parser::parseBinary(int prec, std::unique_ptr<Expression> lhs) {
  // The loop below works by comparing the _binding_ power
  // of the operator we are currently parsing. The logic
  // is to check for the minimal operator precedence that will
  // keep the loop spinning. For example, if the current stream is
  // [+, x] and we pass in, say, `*`, which has a precedence of 40,
  // the loop will break, because `+` only has a precedence of 20.
  while (true) {
    int currPrec = getCurrentTokenPrecedence();
    if (currPrec < prec) {
      return lhs;
    }

    // At this point we're sure that we have a
    // binop with a valid binding power.
    TokenType op = current_.tokenType();
    // Consume the operator.
    advance();

    // Now, we construct an RHS by calling into parsePrimary().
    auto rhs = parsePrimary();
    if (!rhs) {
      return nullptr;
    }

    // If the operator before RHS has a lower precedence than the operator
    // after RHS, let the operator after RHS take the RHS as its LHS.
    // For example, say we're parsing `1 + 1 / 2`. On the first pass, we have
    // {{1 + 1}, {/ 2}}. The first RHS is the second `1`, and the operator
    // before that, `+` has a lower precedence than `*`, the operator after.
    // The algorithm now decides that instead of the whole LHS, which would be
    // `1+1`, only the last `1` should bind to `/2`, producing something
    // equivalent to `(1 + (1/2))`, which is mathematically correct.
    int pendingPrec = getCurrentTokenPrecedence();
    if (currPrec < pendingPrec) {
      rhs = parseBinary(currPrec + 1, std::move(rhs));
      if (!rhs) {
        return nullptr;
      }
    }

    // Now merge the whole AST.
    lhs =
        std::make_unique<BinaryExpression>(std::move(lhs), op, std::move(rhs));
  }
}

} // namespace frontend
} // namespace grace
