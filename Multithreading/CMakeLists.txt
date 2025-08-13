cmake_minimum_required(VERSION 3.31)
project(functions)

set(CMAKE_CXX_STANDARD 20)

add_executable(multithreading
        multithreading.cpp
        thread_synchronization.cpp
)

