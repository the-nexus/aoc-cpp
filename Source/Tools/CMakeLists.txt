
#######################
## Configure library ##

project (AdventOfCodeTools)
set (LIBRARY_ALIAS_NAME AOC::Tools)

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
