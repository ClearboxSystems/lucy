add_subdirectory(test)

add_subdirectory(parser)
add_subdirectory(ast)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(lucy 
    lucy.cpp
)
set_target_properties(
    lucy PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11"
)
target_link_libraries(lucy 
    ${LLVM_LIBRARIES}
    ${LLVM_LDFLAGS}
    parser 
    ast 
)