cmake_minimum_required(VERSION 3.28)
project(hydra)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_subdirectory(src)
add_subdirectory(tests)
