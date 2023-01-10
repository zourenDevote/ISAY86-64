cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_SOURCE_DIR}/third_party/antlr4/runtime/src/)
link_directories(${CMAKE_SOURCE_DIR}/build/third_party/antlr4/runtime)

set(CMAKE_CXX_STANDARD 17)

project(y8664)

add_subdirectory(error)
add_subdirectory(util)
add_subdirectory(emulator)
add_subdirectory(assember)
add_subdirectory(program)
add_subdirectory(third_party)





