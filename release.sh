#!/bin/sh

mkdir -p out
cd out
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DGCRISP_BUILD_TESTS=yes -S .. -B .
