#!/usr/bin/env bash

# Remove old executable
rm column;

# Make MakeFile
cmake CMakeLists.txt;

# Build the project
make |& ./colorize.sh;

# Run the project
./column |& ./colorize.sh;
