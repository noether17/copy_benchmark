cmake_minimum_required(VERSION 4.0.0)
project(memcpy_benchmark LANGUAGES CXX)

find_package(benchmark 1.8.2 REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

add_subdirectory(src)
add_subdirectory(benchmark)
