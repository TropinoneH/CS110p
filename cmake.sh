#!/bin/bash

/usr/local/applications/jetbrains/clion/bin/cmake/linux/x64/bin/cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=/usr/local/applications/jetbrains/clion/bin/ninja/linux/x64/ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S /home/mspt5/Documents/C++/CS110/homework6-TropinoneH -B /home/mspt5/Documents/C++/CS110/homework6-TropinoneH/cmake-build-debug

/usr/local/applications/jetbrains/clion/bin/cmake/linux/x64/bin/cmake --build /home/mspt5/Documents/C++/CS110/homework6-TropinoneH/cmake-build-debug --target hw6 -j 18

./cmake-build-debug/hw6
