#!/bin/bash

cmake --build .       # build the project
if [ $? -eq 0 ]; then # check if build succeeded
  ./kaizen -verbose   # run the executable (will run the tests)
else
  echo "Build failed. Exiting."
  exit 1
fi