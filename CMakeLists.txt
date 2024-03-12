cmake_minimum_required(VERSION 3.27)
project(Lab1 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Wvla -Werror -m64")

add_executable(Lab1 main.c)
