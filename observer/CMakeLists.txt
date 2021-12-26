cmake_minimum_required(VERSION 3.10)
include_directories("./")
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(DesignPattern)

add_executable(DesignPattern main.cpp)
