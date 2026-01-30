cmake_minimum_required(VERSION 4.0.0)
project(memcpy_benchmark LANGUAGES CXX)

find_package(benchmark 1.8.2 REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -Wall \
  -Wextra \
  -Wpedantic \
  -Werror \
  -O3 \
  -march=native \
  -mtune=native \
  -save-temps \
  -masm=intel"
)

include_directories(include)
add_subdirectory(include)
add_subdirectory(benchmark)
add_subdirectory(src)
