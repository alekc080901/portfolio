cmake_minimum_required(VERSION 2.8)
project(Laba2)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(SRC_LIST laba2.c)

add_executable(${PROJECT_NAME} ${SRC_LIST})