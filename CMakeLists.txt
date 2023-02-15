cmake_minimum_required(VERSION 3.24)
project(Ass3)

set(CMAKE_CXX_STANDARD 17)
#set(GCC_COVERAGE_COMPILE_FLAGS "−Wall −ansi −Wpedantic −Wextra")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
# -Weffc++ -pedantic -fPIE -std=c++17
set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_FLAGS -Wextra)
set(CMAKE_CXX_FLAGS -Weffc++)
set(CMAKE_CXX_FLAGS -Wsign-compare)
set(CMAKE_CXX_FLAGS -Wfatal-errors)
set(CMAKE_CXX_FLAGS -std=c++17)


add_executable(Ass3 main.cpp Huffman.cpp Huffman.h PriorityHeap.h Diff.cpp Diff.h)
