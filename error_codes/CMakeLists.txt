project(untitled)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
ADD_DEFINITIONS(
-std=c++11 -Wall -Werror -O3
)
add_executable(${PROJECT_NAME} ${SRC_LIST})

