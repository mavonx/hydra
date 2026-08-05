cmake_minimum_required(VERSION 3.28)
project(hydra)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")
file(GLOB MAIN_SOURCE "src/main.cpp")
list(REMOVE_ITEM CORE_SOURCES ${MAIN_SOURCE})

add_library(hydra_core ${CORE_SOURCES})
target_include_directories(hydra_core PUBLIC include)

add_executable(hydra src/main.cpp)
target_link_libraries(hydra PRIVATE hydra_core)
