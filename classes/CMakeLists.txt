cmake_minimum_required(VERSION 3.31)
project(polymorphism)

set(CMAKE_CXX_STANDARD 20)

add_executable(classes classes.cpp)
add_executable(copy_constructor copy_constructor.cpp.cpp)
add_executable(tests_copy_assignment_problems tests_copy_assignment_problems.cpp)
