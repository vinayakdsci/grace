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

#include "grace/frontend/ast.h"
#include <llvm/Support/ErrorHandling.h>
#include <llvm/Support/raw_ostream.h>

namespace grace {
namespace frontend {

ConstantValue IntegerExpression::accept() { return ConstantValue(value_); }
ConstantValue FloatExpression::accept() { return ConstantValue(value_); }
ConstantValue BinaryExpression::accept() {
  switch (op_) {
  case TokenType::Plus:
    return std::move(left_->accept()) + std::move(right_->accept());
  case TokenType::Star:
    return std::move(left_->accept()) * std::move(right_->accept());
  case TokenType::Slash:
    return std::move(left_->accept()) / std::move(right_->accept());
  case TokenType::Minus:
    return std::move(left_->accept()) - std::move(right_->accept());
  default:
    llvm_unreachable("Unsupported operator in binary expression");
  }
}
} // namespace frontend
} // namespace grace
