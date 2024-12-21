#!/bin/bash


if not [ -d ./out/ ] || [ -n "$(find "./out/" -maxdepth 0 -type d -empty 2>/dev/null)" ]; then
  echo "Could not find target to build!"
  echo "Please generate a target using either the debug.sh or release.sh script."
  exit 1
fi

cd out
cmake --build . -j 
