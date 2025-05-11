#!/bin/sh

mkdir -p out
cd out
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ -DGCRISP_BUILD_TESTS=yes -S .. -B .
