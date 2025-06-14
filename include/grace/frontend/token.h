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

#ifndef GRACE_INCLUDE_TOKEN_H_
#define GRACE_INCLUDE_TOKEN_H_

#include <llvm/Support/ErrorHandling.h>

#include <cassert>
#include <optional>

namespace {
union ConstantValueContents {
  double float_constant_;
  long long int_constant_;
};
}  // namespace

namespace grace {
namespace frontend {

enum ConstantTag {
  FloatConstant,
  IntegerConstant,
};

enum class TokenType {
  Constant,

  // Operators.
  Plus,
  Minus,
  Star,
  Slash,

  // Special Tokens.
  Error,
  Eof,
};

struct ConstantValue {
  ConstantValue(long long int_constant) : type_tag_(IntegerConstant) {
    contents_ = ConstantValueContents{
        .int_constant_ = int_constant,
    };
  }

  ConstantValue(double float_constant) : type_tag_(FloatConstant) {
    contents_ = ConstantValueContents{
        .float_constant_ = float_constant,
    };
  }

  const bool isIntegerConstant() const { return type_tag_ == IntegerConstant; }
  const bool isFloatConstant() const { return type_tag_ == FloatConstant; }

  const ConstantTag tag() const { return type_tag_; }

  const bool operator==(ConstantValue& other) const {
    if (type_tag_ != other.tag()) {
      return false;
    }

    switch (type_tag_) {
      case IntegerConstant:
        return contents_.int_constant_ == other.intConstant();
      case FloatConstant:
        return contents_.float_constant_ == other.floatConstant();
      default:
        llvm_unreachable("Unsupported constant type.");
    }
  }

  std::string toString();

  const double& floatConstant() const;
  const long long& intConstant() const;

 private:
  ConstantTag type_tag_;
  ConstantValueContents contents_;
};

struct Token {
  Token(TokenType tt) : token_type_(tt), constant_token_value_(std::nullopt) {}
  Token(TokenType tt, long long int_constant)
      : token_type_(tt), constant_token_value_(ConstantValue(int_constant)) {}
  Token(TokenType tt, double float_constant)
      : token_type_(tt), constant_token_value_(ConstantValue(float_constant)) {}

  const TokenType& tokenType() const { return token_type_; }

  const std::optional<ConstantValue>& constantTokenValue() const {
    return constant_token_value_;
  }

  const bool operator==(Token& other) const {
    if (token_type_ != other.tokenType()) {
      return false;
    }

    if (token_type_ == other.token_type_ &&
        !constant_token_value_.has_value() &&
        !other.constantTokenValue().has_value()) {
      return true;
    }
    return *constant_token_value_ ==
           const_cast<ConstantValue&>(other.constantTokenValue().value());
  }

  std::string toString();

 private:
  TokenType token_type_;
  std::optional<ConstantValue> constant_token_value_;
};

}  // namespace frontend
}  // namespace grace
#endif
