cmake_minimum_required(VERSION 3.10)
project(TravelingSalesman)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES TSP.cpp)
add_executable(TravelingSalesman ${SOURCE_FILES})

target_compile_definitions(TravelingSalesman PUBLIC -DPROJECT_DIRECTORY="${CMAKE_SOURCE_DIR}")