file(GLOB AST_SOURCES *.cc)

add_library(codegen ${AST_SOURCES})
set_target_properties(
    codegen PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11 ${LLVM_CXXFLAGS}"
)
target_include_directories(codegen PRIVATE ${LLVM_INCLUDE_DIRS})