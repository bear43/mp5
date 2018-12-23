cmake_minimum_required(VERSION 3.13)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

link_libraries("/usr/local/lib/libfmt.a")

add_executable(untitled main.cpp Point.cpp Point.h Object.h Map.cpp Map.h)