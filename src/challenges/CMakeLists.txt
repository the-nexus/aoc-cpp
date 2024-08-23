
#######################
## Configure library ##

project (AdventOfCode_Challenges CXX)
set (LIBRARY_ALIAS_NAME aoc::challenges)

#####################
## Auto Generation ##

set(AUTOGEN_DIR ${PROJECT_SOURCE_DIR}/challenges${AUTOGEN_SUB_PATH})
set(AUTOGEN_COMMAND ${SCRIPT_COMMAND} ${SCRIPT_DIR}/${SCRIPT_AUTOGEN_CHALLENGE_REGISTRY})
set(AUTOGEN_ARGS ${PROJECT_SOURCE_DIR} ${AUTOGEN_DIR} ${SCRIPT_OPT_DEBUG})

message (${AUTOGEN_COMMAND})
execute_process (
    COMMAND ${AUTOGEN_COMMAND} ${AUTOGEN_ARGS}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

#####################
## Create library ##

file (GLOB_RECURSE FILES_SOURCE ${PROJECT_SOURCE_DIR}/*.c ${PROJECT_SOURCE_DIR}/*.cpp)
file (GLOB_RECURSE FILES_INLINE ${PROJECT_SOURCE_DIR}/*.inl)
file (GLOB_RECURSE FILES_HEADER ${PROJECT_SOURCE_DIR}/*.h ${PROJECT_SOURCE_DIR}/*.hpp)

source_group (TREE ${PROJECT_SOURCE_DIR} FILES ${FILES_SOURCE} ${FILES_INLINE} ${FILES_HEADER})

add_library (${PROJECT_NAME} STATIC ${FILES_SOURCE} ${FILES_INLINE} ${FILES_HEADER})
add_library (${LIBRARY_ALIAS_NAME} ALIAS ${PROJECT_NAME})

set_target_properties (${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories (${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

#######################
## Link dependencies ##

target_link_libraries (${PROJECT_NAME}
    PRIVATE aoc::core
)
