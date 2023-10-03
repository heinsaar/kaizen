#!/bin/bash

# Initialize variables to store any arguments
ARG_CLOC=""
BUILD_TYPE="Debug"  # Default to Release build

# Parse named arguments
for arg in "$@"; do
  case $arg in
    -cloc)
      ARG_CLOC="-cloc"
      ;;
    -debug)
      BUILD_TYPE="Debug"
      ;;
    -release)
      BUILD_TYPE="Release"
      ;;
    *)
      # Handle or ignore other arguments
      ;;
  esac
done

cmake --build . --config $BUILD_TYPE # build the project
if [ $? -eq 0 ]; then                # check if build succeeded
    ./kaizen -verbose $ARG_CLOC      # run the executable (will run the tests)
else
  echo "Build failed. Exiting."
  exit 1
fi