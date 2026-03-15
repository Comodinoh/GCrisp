#!/bin/sh

mkdir -p out
cd out
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DVANE_BUILD_TESTS=yes -S .. -B .
