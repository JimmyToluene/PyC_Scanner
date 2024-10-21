cmake_minimum_required(VERSION 3.29)
project(Scanner)

set(CMAKE_CXX_STANDARD 20)

add_executable(Scanner main.cpp
        dfa.cpp
        scanner.h
        list.cpp
)
