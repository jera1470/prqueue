cmake_minimum_required(VERSION 3.27)
project(prqueue)
add_subdirectory(Google_tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(prqueue prqueue_main.cpp)
