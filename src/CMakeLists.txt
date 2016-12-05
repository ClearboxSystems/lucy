add_subdirectory(test)

add_subdirectory(parser)
add_subdirectory(ast)

add_executable(lucy 
    lucy.cpp
)
set_target_properties(
    lucy PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11 -Wno-deprecated-register"
)
target_link_libraries(lucy 
    ${LLVM_LIBRARIES}
    ${LLVM_LDFLAGS}
    parser 
    ast 
)