#!/bin/sh

SOLUTION_DIR="bin/"
SOURCE_DIR="source/"

#create the solution directory if it doesn't exist then move to it
if [ ! -d $SOLUTION_DIR ]; then
    mkdir $SOLUTION_DIR
fi

cd $SOLUTION_DIR

#generate (or regenerate) the solution right here based on the CMakeList.txt in the source folder
cmake ../$SOURCE_DIR
