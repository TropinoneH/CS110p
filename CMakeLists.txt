cmake_minimum_required(VERSION 3.27)
project(hw6 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -lm -g -std=c11 -Wpedantic -Wall -Wextra -Werror -Wvla")

add_executable(hw6 main.c cache.c cache.h)