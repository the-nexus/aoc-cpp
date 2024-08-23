
add_subdirectory (./challenges)
add_subdirectory (./core)

##########################
## Configure executable ##

project (AdventOfCode CXX)

#######################
## Create executable ##

add_executable (${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Main.cpp)

target_link_libraries (${PROJECT_NAME}
    PRIVATE aoc::challenges
    PRIVATE aoc::core
)
