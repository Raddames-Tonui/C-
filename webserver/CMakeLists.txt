cmake_minimum_required(VERSION 3.31)
project(webserver)

set(CMAKE_CXX_STANDARD 20)

add_executable(webserver
        src/main.cpp
)

find_package(Drogon REQUIRED)
find_package(PostgreSQL REQUIRED)
target_link_libraries(webserver PRIVATE Drogon::Drogon  PostgreSQL::PostgreSQL)

