
add_subdirectory (./Challenges)
add_subdirectory (./Tools)

##########################
## Configure executable ##

project (AdventOfCode CXX)

#######################
## Create executable ##

add_executable (${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Main.cpp)

target_link_libraries (${PROJECT_NAME}
    PRIVATE AOC::Challenges
    PRIVATE AOC::Tools
)
