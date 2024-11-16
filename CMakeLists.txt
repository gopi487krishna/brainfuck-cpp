cmake_minimum_required(VERSION 3.10)
project(brainfuck-cpp VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)
add_subdirectory(src)


