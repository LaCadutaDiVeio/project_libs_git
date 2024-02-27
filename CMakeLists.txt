cmake_minimum_required(VERSION 3.8)
project(project_libs C)

set(CMAKE_C_STANDARD 11)

include("libs/CMakeLists.txt")

set (src_files
        ${src_libs}
        main.c
)

add_executable(project_libs ${src_files})

target_sources (project_libs PRIVATE ${src_files})
source_group (TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${src_files})
