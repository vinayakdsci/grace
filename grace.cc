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
#include "grace/frontend/parser.h"
#include <llvm/Support/raw_ostream.h>

namespace frontend = grace::frontend;

int main() {
  const char *source = "1.1 / 2.2 + 0.5"; // Should dump 1.0
  frontend::Lexer lexer = frontend::Lexer(source);
  frontend::Parser parser = frontend::Parser(&lexer);

  frontend::ConstantValue cval = parser.eval();

  cval.dump('\n');
  return 0;
}
