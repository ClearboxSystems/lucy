#add_executable(lucy lucy.cpp)
#set_target_properties(
#    lucy PROPERTIES
#    COMPILE_FLAGS "-O3 ${LLVM_CXXFLAGS}"
#    LINK_FLAGS "-pthread"
#)
#target_include_directories(lucy PRIVATE ${LLVM_INCLUDE_DIRS})
#target_link_libraries(lucy ${LLVM_LIBRARIES} ${LLVM_LDFLAGS})

BISON_TARGET(LucyParser lucy.yy ${CMAKE_CURRENT_BINARY_DIR}/lucy.tab.cpp)
FLEX_TARGET(LucyScanner lucy.lex ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(LucyScanner LucyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(token 
    ${BISON_LucyParser_OUTPUTS} 
    ${FLEX_LucyScanner_OUTPUTS}
)
set_target_properties(
    token PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11"
)
target_link_libraries(
    token
    fl
)
