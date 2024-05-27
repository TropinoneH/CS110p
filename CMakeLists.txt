cmake_minimum_required(VERSION 3.27)
project(lab13 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=gnu11 -fopenmp")

add_executable(lab13-3 dotp.c)
add_executable(lab13-1 hello.c)
add_executable(lab13-2 matmul.c)
