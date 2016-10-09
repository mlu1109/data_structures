cmake_minimum_required(VERSION 3.6)
project(data_structures)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(SOURCE_FILES main.cpp avl.hpp)
add_executable(data_structures ${SOURCE_FILES})

add_subdirectory(lib/gtest-1.8.0/googletest)
add_subdirectory(test)
include_directories(lib/gtest-1.8.0/googletest/include)
