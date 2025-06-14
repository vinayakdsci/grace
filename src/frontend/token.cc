#include "grace/frontend/token.h"

#include <string>

namespace grace {
namespace frontend {

///////////////////////////////////////////////////////////
/// ConstantValue
//////////////////////////////////////////////////////////
const long long& ConstantValue::intConstant() const {
  assert(type_tag_ == IntegerConstant &&
         "Cannot interpret Float constant as Integer.");

  return contents_.int_constant_;
}

const double& ConstantValue::floatConstant() const {
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

}  // namespace frontend
}  // namespace grace
