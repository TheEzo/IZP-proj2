cmake_minimum_required(VERSION 3.6)
project(proj2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wall -Werror -Wextra")

set(SOURCE_FILES proj2.c)
add_executable(proj2 ${SOURCE_FILES})