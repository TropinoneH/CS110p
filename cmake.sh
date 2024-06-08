cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S ./ -B ./cmake-build-debug

cmake --build ./cmake-build-debug --target test -j 18

./cmake-build-debug/test
