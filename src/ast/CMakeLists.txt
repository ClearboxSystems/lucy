file(GLOB AST_SOURCES *.cc)

add_library(ast ${AST_SOURCES})
set_target_properties(
    ast PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11 ${LLVM_CXXFLAGS}"
)
target_include_directories(ast PRIVATE ${LLVM_INCLUDE_DIRS})