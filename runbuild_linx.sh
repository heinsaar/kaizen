#!/bin/bash

# Build the CMake project
cmake --build .

# Check if build succeeded
if [ $? -eq 0 ]; then
  # Run the executable
  ./kaizen
else
  echo "Build failed. Exiting."
  exit 1
fi