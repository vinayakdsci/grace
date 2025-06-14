cmake_minimum_required(VERSION 3.29.0)

project(Grace)

# Boilerplate setup code
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require the user to install the LLVM binary beforehand.
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# Link the executable target to LLVM.
add_executable(grcc grace.cc)
llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(grcc ${llvm_libs})

# Configure the include/ dir.
target_include_directories(grcc PUBLIC include)

# Configure the src/ dir.
add_subdirectory(src)
target_link_libraries(grcc grcc_src)

# Configure the test/ dir.
# include(CTest)
# enable_testing()
# add_subdirectory(test)

# Copy back the compile_command.json file from the build dir
# to the top level if the editor is not Visual Studio, as a
# quality-of-life improvement.
if(NOT CMAKE_GENERATOR MATCHES "Visual Studio")
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
        DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
        COMMENT "Copying compile_commands.json..."
    )

    add_custom_target(copy_compile_commands ALL
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()
