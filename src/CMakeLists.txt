project(Grace)

add_library(grcc_src INTERFACE)
add_subdirectory(frontend)
target_link_libraries(grcc_src INTERFACE grcc_frontend)
