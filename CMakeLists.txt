project(clecc)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
aux_source_directory(./src SRC_LIST)

ADD_DEFINITIONS(-DCL_SOURCE_DIR="./src")

add_executable(${PROJECT_NAME} ${SRC_LIST})


