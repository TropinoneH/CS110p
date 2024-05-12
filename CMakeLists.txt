cmake_minimum_required(VERSION 3.27)
project(lab11 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -Wpedantic -Werror -std=gnu11 -O3 -march=native")

add_executable(lab11 part2_3.c)
