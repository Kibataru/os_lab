cmake_minimum_required(VERSION 3.15)
project(OS_LAB0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(os_lab0 lab0.c base.c)
