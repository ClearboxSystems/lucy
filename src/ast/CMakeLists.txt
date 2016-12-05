file(GLOB AST_SOURCES *.cpp)

add_library(ast ${AST_SOURCES})
set_target_properties(
    ast PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11"
)
