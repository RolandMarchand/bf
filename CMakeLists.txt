cmake_minimum_required(VERSION 3.22)

project(bf VERSION 0.1
  LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set(CMAKE_C_COMPILER gcc)

add_executable(bf bf.c)
