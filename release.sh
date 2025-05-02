#!/bin/sh

mkdir -p out
cd out
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DGCRISP_BUILD_TESTS=yes -S .. -B .
