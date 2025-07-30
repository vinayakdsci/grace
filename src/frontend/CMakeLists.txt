# Copyright 2025 Vinayak Dev
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# This file is intentionally kept very simple.
# It should grow into something much more complex
# as the project increases in size and complexity.
# Add all the source files here.
set(GRCC_FRONTEND_SRC_FILES
	token.cc
	lexer.cc
	parser.cc
)

add_library(grcc_frontend ${GRCC_FRONTEND_SRC_FILES})
target_include_directories(grcc_frontend PUBLIC ../../include/)
