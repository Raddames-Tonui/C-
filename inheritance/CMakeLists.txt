cmake_minimum_required(VERSION 3.31)
project(inheritance)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)
add_executable(shared_pointers shared_pointers.cpp)
add_executable(abc abc.cpp)
add_executable(bank bank.cpp)
add_executable(diamond_inheritance diamond_inheritance.cpp)
