cmake_minimum_required(VERSION 3.10)

PROJECT(homework3)

include_directories(inc)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -Werror -Wpedantic -Wvla")

file(GLOB SRC "src/*.c")

add_executable(fks test_fks.c ${SRC})