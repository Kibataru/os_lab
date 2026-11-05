cmake_minimum_required(VERSION 3.15)
project(ProcessRunnerLib C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(lib STATIC lib.c)

add_executable(test_runner main.c)

target_link_libraries(test_runner PRIVATE lib)