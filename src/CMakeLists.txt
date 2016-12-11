add_subdirectory(parser)
add_subdirectory(ast)
add_subdirectory(codegen)

#message (STATUS "LLVM_FOUND: " ${LLVM_FOUND})
#message (STATUS "LLVM_CXXFLAGS: " ${LLVM_CXXFLAGS})
#message (STATUS "LLVM_HOST_TARGET: " ${LLVM_HOST_TARGET})
#message (STATUS "LLVM_INCLUDE_DIRS: " ${LLVM_INCLUDE_DIRS})
#message (STATUS "LLVM_LDFLAGS: " ${LLVM_LDFLAGS})
#message (STATUS "LLVM_LIBRARIES: " ${LLVM_LIBRARIES})
#message (STATUS "LLVM_LIBRARY_DIRS: " ${LLVM_LIBRARY_DIRS})
#message (STATUS "LLVM_ROOT_DIR: " ${LLVM_ROOT_DIR})
#message (STATUS "LLVM_VERSION_MAJOR: " ${LLVM_VERSION_MAJOR})
#message (STATUS "LLVM_VERSION_MINOR: " ${LLVM_VERSION_MINOR})
#message (STATUS "LLVM_VERSION_STRING: " ${LLVM_VERSION_STRING})

message (STATUS "TEST: " ${CMAKE_SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(lucy 
    lucy.cpp
)
set_target_properties(
    lucy PROPERTIES
    COMPILE_FLAGS "-O3 -g -std=c++11 ${LLVM_CXXFLAGS}"
#    LINK_FLAGS "-pthread"
)
target_link_libraries(lucy 
    parser 
    ast 
    codegen
    ${LLVM_LIBRARIES}
    ${LLVM_LDFLAGS}
)
target_include_directories(lucy PRIVATE ${LLVM_INCLUDE_DIRS})