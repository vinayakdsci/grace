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
#include "grace/frontend/token.h"

#include <iostream>
#include <string>

namespace grace {
namespace frontend {

///////////////////////////////////////////////////////////
/// ConstantValue
//////////////////////////////////////////////////////////
const long long &ConstantValue::intConstant() const {
  assert(type_tag_ == IntegerConstant &&
         "Cannot interpret Float constant as Integer.");

  return contents_.int_constant_;
}

const double &ConstantValue::floatConstant() const {
  assert(type_tag_ == FloatConstant &&
         "Cannot interpret Integer constant as Float.");

  return contents_.float_constant_;
}

std::string ConstantValue::toString() {
  std::string s = "";

  const auto contentsToStr = [&]() -> std::string {
    switch (type_tag_) {
    case IntegerConstant: {
      std::string contents = std::to_string(intConstant());
      return "{Integer: " + contents + "}";
    }
    case FloatConstant: {
      std::string contents = std::to_string(floatConstant());
      return "{Float: " + contents + "}";
    }
    default:
      llvm_unreachable("Unsupported constant type.");
    }
  };
  s = "{Constant: " + contentsToStr() + "}";
  return s;
}

void ConstantValue::print(std::ostream &ostream) { ostream << toString(); }
void ConstantValue::print(llvm::raw_ostream &ostream) { ostream << toString(); }
void ConstantValue::print(llvm::raw_fd_ostream &ostream) {
  ostream << toString();
}
void ConstantValue::print(std::ostream &ostream, const char end) {
  ostream << toString() << end;
}
void ConstantValue::print(llvm::raw_ostream &ostream, const char end) {
  ostream << toString() << end;
}
void ConstantValue::print(llvm::raw_fd_ostream &ostream, const char end) {
  ostream << toString() << end;
}
void ConstantValue::dump() { print(std::cout); }
void ConstantValue::dump(const char end) { print(std::cout, end); }

///////////////////////////////////////////////////////////
/// Token
//////////////////////////////////////////////////////////
std::string Token::toString() {
  std::string s = "";

  const auto strHelper = [](std::string s) -> std::string {
    return "{TokenType: " + s + "}";
  };

  const auto tokTypeToStr = [&]() -> std::string {
    switch (token_type_) {
    case TokenType::Constant: {
      std::string contents = constant_token_value_->toString();
      return strHelper(contents);
    }
    case TokenType::Eof:
      return strHelper("Eof");
    case TokenType::Plus:
      return strHelper("Plus");
    case TokenType::Star:
      return strHelper("Star");
    case TokenType::Slash:
      return strHelper("Slash");
    case TokenType::Minus:
      return strHelper("Minus");
    default:
      llvm_unreachable("Unsupported constant type.");
    }
  };

  s = "{Token: " + tokTypeToStr() + "}";
  return s;
}

void Token::print(std::ostream &ostream) { ostream << toString(); }
void Token::print(llvm::raw_ostream &ostream) { ostream << toString(); }
void Token::print(llvm::raw_fd_ostream &ostream) { ostream << toString(); }
void Token::print(std::ostream &ostream, const char end) {
  ostream << toString() << end;
}
void Token::print(llvm::raw_ostream &ostream, const char end) {
  ostream << toString() << end;
}
void Token::print(llvm::raw_fd_ostream &ostream, const char end) {
  ostream << toString() << end;
}
void Token::dump() { print(std::cout); }
void Token::dump(const char end) { print(std::cout, end); }

} // namespace frontend
} // namespace grace
