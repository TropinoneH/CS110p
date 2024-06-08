/usr/local/applications/jetbrains/clion/bin/cmake/linux/x64/bin/cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=/usr/local/applications/jetbrains/clion/bin/ninja/linux/x64/ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S ./ -B ./cmake-build-debug

/usr/local/applications/jetbrains/clion/bin/cmake/linux/x64/bin/cmake --build ./cmake-build-debug --target test -j 18

./cmake-build-debug/test
