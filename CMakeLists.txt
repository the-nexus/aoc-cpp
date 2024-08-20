
#############
## GLOBALS ##

cmake_minimum_required (VERSION 3.22)

set (CMAKE_CXX_STANDARD 20)

set (SCRIPT_COMMAND python3)
set (SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Scripts)
set (SCRIPT_GENERATE_CHALLENGE_REGISTRY GenerateChallengeRegistry.py)
set (SCRIPT_OPT_DEBUG -v)

#############
## PROJECT ##

project (AdventOfCode
    DESCRIPTION "C++ Advent of Code solution (https://adventofcode.com/) "
    HOMEPAGE_URL "https://github.com/the-nexus/aoc-cpp"
    LANGUAGES CXX
)

add_subdirectory(./Source)
