
#######################
## Configure library ##

project (AdventOfCode_Tests CXX)

file (GLOB_RECURSE FILES_SOURCE ${PROJECT_SOURCE_DIR}/*.c ${PROJECT_SOURCE_DIR}/*.cpp)
file (GLOB_RECURSE FILES_INLINE ${PROJECT_SOURCE_DIR}/*.inl)
file (GLOB_RECURSE FILES_HEADER ${PROJECT_SOURCE_DIR}/*.h ${PROJECT_SOURCE_DIR}/*.hpp)

source_group (TREE ${PROJECT_SOURCE_DIR} FILES ${FILES_SOURCE} ${FILES_INLINE} ${FILES_HEADER})

########################
## Create executables ##

add_executable (Tests_Intcode2019 ${PROJECT_SOURCE_DIR}/tests/Tests_Intcode2019.cpp)

target_link_libraries (Tests_Intcode2019
    PRIVATE aoc::runtime
)
