#!/bin/bash

mkdir -p out
cd out
cmake -DCMAKE_BUILD_TYPE=Debug -S .. -B .
