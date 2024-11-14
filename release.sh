#!/bin/bash

mkdir -p out/release
cd out/release
cmake --build .. -j --config Release
