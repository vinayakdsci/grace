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

#ifndef GRACE_AST_H_
#define GRACE_AST_H_

#include "grace/frontend/token.h"
#include <memory>

namespace grace {
namespace frontend {
class IntegerExpression;
class FloatExpression;
class BinaryExpression;
class UnaryExpression;

class Expression {
public:
  virtual ~Expression() = default;
  virtual ConstantValue accept() = 0;
};

class IntegerExpression : public Expression {
public:
  IntegerExpression(long long value) : value_(value) {}

  ConstantValue accept() override;

private:
  long long value_;
};

class FloatExpression : public Expression {
public:
  FloatExpression(double value) : value_(value) {}

  ConstantValue accept() override;

private:
  double value_;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression(std::unique_ptr<Expression> left, TokenType op,
                   std::unique_ptr<Expression> right)
      : left_(std::move(left)), op_(op), right_(std::move(right)) {}

  ConstantValue accept() override;

private:
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
  TokenType op_;
};

} // namespace frontend
} // namespace grace
#endif
