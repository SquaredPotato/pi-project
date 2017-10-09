#!/usr/bin/env bash

# Remove old executable
rm column;

# Make MakeFile
cmake CMakeLists.txt;

# Build the project
make;

# Run the project
sudo ./column;
