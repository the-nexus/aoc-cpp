
cmake_minimum_required (VERSION 3.22)

##################
## DEPENDENCIES ##

find_package (Python REQUIRED COMPONENTS Interpreter)

#############
## GLOBALS ##

# C++
set (CMAKE_CXX_STANDARD 20)

# SCRIPTING
set (SCRIPT_COMMAND ${Python_EXECUTABLE})
set (SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Scripts)
set (SCRIPT_AUTOGEN_CHALLENGE_REGISTRY GenerateChallengeRegistry.py)
#set (SCRIPT_OPT_DEBUG -v)

set (AUTOGEN_SUB_PATH /Autogen)

#############
## PROJECT ##

project (AdventOfCode
    DESCRIPTION "C++ Advent of Code solution (https://adventofcode.com/) "
    HOMEPAGE_URL "https://github.com/the-nexus/aoc-cpp"
    LANGUAGES CXX
)

add_subdirectory(./Source)
