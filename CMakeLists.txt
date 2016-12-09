cmake_minimum_required (VERSION 2.8)
project (Lucy)

#This removes the warnings from the FindLLVM script as it uses a if ("true") style which is deprecated
cmake_policy(SET CMP0012 OLD)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(LLVM 3.8 REQUIRED core mcjit native)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

