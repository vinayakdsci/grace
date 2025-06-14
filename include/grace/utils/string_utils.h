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

#ifndef GRACE_UTILS_STRING_UTILS_H_
#define GRACE_UTILS_STRING_UTILS_H_

namespace grace {
namespace utils {

inline const bool isDigit(const char ch) { return '0' <= ch && ch <= '9'; }
inline const bool isAsciiUppercaseAlphabet(const char ch) {
  return 'A' <= ch && ch <= 'Z';
}
inline const bool isAsciiLowercaseAlphabet(const char ch) {
  return 'a' <= ch && ch <= 'z';
}
inline const bool isAsciiAlphabet(const char ch) {
  return isAsciiLowercaseAlphabet(ch) || isAsciiUppercaseAlphabet(ch);
}
inline const bool isWhiteSpace(const char ch) {
  return ch == ' ' || ch == '\t';
}
inline const bool isAsciiWhitespace(const char ch) {
  return isWhiteSpace(ch) || ch == '\n' || ch == '\r';
}

} // namespace utils
} // namespace grace

#endif
