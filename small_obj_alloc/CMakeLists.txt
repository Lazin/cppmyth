project(small_obj_alloc)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
ADD_DEFINITIONS(
-std=c++11 -Wall -Werror
)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} jemalloc boost_system)

