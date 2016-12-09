find_package(BISON 3)
find_package(FLEX 2.5)

BISON_TARGET(BisonParser
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar.yy
  ${CMAKE_CURRENT_BINARY_DIR}/BisonParser.cc)

FLEX_TARGET(FlexLexer
  ${CMAKE_CURRENT_SOURCE_DIR}/lexer.ll
  ${CMAKE_CURRENT_BINARY_DIR}/FlexLexer.cc)

ADD_FLEX_BISON_DEPENDENCY(FlexLexer BisonParser)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
set(PARSER_SOURCES
    Parser.cc
    Lexer.cc
)

add_library(parser
  ${PARSER_SOURCES}
  ${BISON_BisonParser_OUTPUTS}
  ${FLEX_FlexLexer_OUTPUTS}
)

set_target_properties(
    parser PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11 -Wno-deprecated-register "
)
