cmake_minimum_required(VERSION 3.27)
project(Lab2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wvla")

add_executable(Lab2 main.c vector.h vector.c)
