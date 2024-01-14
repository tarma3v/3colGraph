cmake_minimum_required(VERSION 3.26)
project(3paint)

set(CMAKE_CXX_STANDARD 17)

add_executable(3paint main.cpp
        Graph.cpp
        Graph.h
        generate_graphs.hpp
)
