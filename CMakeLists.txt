cmake_minimum_required(VERSION 3.26)
project(regex)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)
add_executable(regex main.cpp
        pcregex.cpp
        pcregex.h)

target_include_directories(regex PUBLIC
        fmt
)
target_link_libraries(regex PUBLIC
        pcre2-8
        fmt::fmt
)
