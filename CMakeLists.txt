
#############
## GLOBALS ##

cmake_minimum_required (VERSION 3.22)

set (CMAKE_CXX_STANDARD 20)

#############
## PROJECT ##

project (AdventOfCode
    DESCRIPTION "C++ Advent of Code solution (https://adventofcode.com/) "
    HOMEPAGE_URL "https://github.com/the-nexus/aoc-cpp"
    LANGUAGES CXX
)

add_subdirectory(./Source)
