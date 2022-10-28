
cmake_minimum_required (VERSION 3.8)

project (AdventOfCode CXX)

file (GLOB_RECURSE SOURCE_LIST *.h* *.c*
)

# Add source to this project's executable.
add_executable (AdventOfCode ${SOURCE_LIST})
target_compile_features (AdventOfCode PRIVATE cxx_std_17)

# Create the source groups for source tree with root at CMAKE_CURRENT_SOURCE_DIR
# https://stackoverflow.com/questions/31422680/how-to-set-visual-studio-filters-for-nested-sub-directory-using-cmake
source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})

