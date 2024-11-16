#!/bin/bash

mkdir -p out
cd out
cmake -DCMAKE_BUILD_TYPE=Debug -DGCRISP_BUILD_TESTS=yes -S .. -B .
