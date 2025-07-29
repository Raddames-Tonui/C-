cmake_minimum_required(VERSION 3.24)
project(Calculator)

# Use C++23 for latest language features
set(CMAKE_CXX_STANDARD 23)

# Include header files from include/
include_directories(include)

# Define the main executable and its sources
add_executable(Calculator
        main.cpp
        src/math_utils.cpp
)
