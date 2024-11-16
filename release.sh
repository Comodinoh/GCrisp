#!/bin/bash

mkdir -p out
cd out
cmake -DCMAKE_BUILD_TYPE=Release -DGCRISP_BUILD_TESTS=no -S .. -B .
