cmake_minimum_required (VERSION 2.8)
project (Lucy)

#This removes the warnings from the FindLLVM script as it uses a if ("true") style which is deprecated
cmake_policy(SET CMP0012 OLD)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(LLVM 3.8 REQUIRED core mcjit native)

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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

