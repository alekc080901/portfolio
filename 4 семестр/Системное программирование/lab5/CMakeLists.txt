cmake_minimum_required(VERSION 3.15)
project(lab5 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab2 algorithm.c server.c algorithm.c socketOperations.c client.c)