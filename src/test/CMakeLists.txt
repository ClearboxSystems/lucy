find_package(BISON 3)
find_package(FLEX 2.5)

BISON_TARGET(parser
  ${CMAKE_CURRENT_SOURCE_DIR}/parser.yy
  ${CMAKE_CURRENT_BINARY_DIR}/calc++-parser.cpp)

FLEX_TARGET(scanner
  ${CMAKE_CURRENT_SOURCE_DIR}/scanner.lex
  ${CMAKE_CURRENT_BINARY_DIR}/calc++-scanner.cpp)

ADD_FLEX_BISON_DEPENDENCY(scanner parser)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(calc
  calc++.cpp
  calc++-driver.cpp
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS})

set_target_properties(
    calc PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11"
)
