
add_subdirectory (./challenges)
add_subdirectory (./core)
add_subdirectory (./runtime)

##########################
## Configure executable ##

project (AdventOfCode CXX)

#######################
## Create executable ##

add_executable (${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Main.cpp)

target_link_libraries (${PROJECT_NAME}
    PRIVATE aoc::runtime
)
