find_package(BISON 3)
find_package(FLEX 2.5)

BISON_TARGET(bparser
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar.yy
  ${CMAKE_CURRENT_BINARY_DIR}/bison_parser.cpp)

FLEX_TARGET(lexer
  ${CMAKE_CURRENT_SOURCE_DIR}/lexer.ll
  ${CMAKE_CURRENT_BINARY_DIR}/flex_lexer.cpp)

ADD_FLEX_BISON_DEPENDENCY(lexer bparser)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(PARSER_SOURCES
    parser.cpp
)

add_library(parser
  ${PARSER_SOURCES}
  ${BISON_bparser_OUTPUTS}
  ${FLEX_lexer_OUTPUTS})

set_target_properties(
    parser PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11"
)
