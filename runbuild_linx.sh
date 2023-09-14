#!/bin/bash

# Initialize variables to store any arguments
CLOCARG=""

# Parse named arguments
for arg in "$@"; do
  case $arg in
    -cloc)
      CLOCARG="-cloc"
      ;;
    *)
      # Handle or ignore other arguments
      ;;
  esac
done

cmake --build .                # build the project
if [ $? -eq 0 ]; then          # check if build succeeded
    ./kaizen -verbose $CLOCARG # run the executable (will run the tests)
else
  echo "Build failed. Exiting."
  exit 1
fi