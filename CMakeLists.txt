cmake_minimum_required(VERSION 3.10)
project(MyProgram LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)


add_compile_options(-fmax-errors=1)


add_executable(testLList testLList.cpp)
add_executable(testBST testBST.cpp)

add_executable(testLLQueue testLLQueue.cpp)