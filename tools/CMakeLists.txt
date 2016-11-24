add_executable(lucy lucy.cpp)
set_target_properties(
    lucy PROPERTIES
    COMPILE_FLAGS "-O3 ${LLVM_CXXFLAGS}"
    LINK_FLAGS "-pthread"
)
target_include_directories(lucy PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(lucy ${LLVM_LIBRARIES} ${LLVM_LDFLAGS})
