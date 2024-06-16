cmake_minimum_required(VERSION 3.14)
project(24f_CS110_Proj4 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -O2 -fno-tree-vectorize -fno-tree-loop-vectorize -fno-tree-slp-vectorize -fopenmp -march=native")

add_executable(test src/test.c src/baseline.c src/impl_oo.c)
add_executable(old src/test.c src/baseline.c src/impl.c)
