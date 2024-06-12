cmake_minimum_required (VERSION 3.8)

file (GLOB_RECURSE SOURCE_LIST Main.cpp
    challenges/*.h* challenges/*.c* challenges/*.inl
    tests/*.h* tests/*.c* tests/*.inl
)
source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})

# Add source to this project's executable.
project (AdventOfCode CXX)
add_executable (${PROJECT_NAME} ${SOURCE_LIST})
target_compile_features (${PROJECT_NAME} PRIVATE cxx_std_20)

# Link children CMakeLists.txt files
add_subdirectory (./tools)

# Link dependencies
target_include_directories (${PROJECT_NAME}
    PUBLIC ./tools
)

target_link_directories (${PROJECT_NAME}
    PUBLIC ./tools
)

target_link_libraries (${PROJECT_NAME}
    AOC_Tools
)