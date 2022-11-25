cmake_minimum_required (VERSION 3.8)
project (AOC_Tools VERSION 0.0.1 LANGUAGES CXX)
message (STATUS ${PROJECT_NAME} ": Version " ${PROJECT_VERSION})

file (GLOB_RECURSE TOOLS_LIST *.h* *.c*)
source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TOOLS_LIST})

add_library (${PROJECT_NAME} ${TOOLS_LIST})
target_compile_features (${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
    LINKER_LANGUAGE CXX
)
