cmake_minimum_required(VERSION 3.27)
project(proj1.2 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Wvla -Werror")

add_executable(proj1.2 Convolution.c)
