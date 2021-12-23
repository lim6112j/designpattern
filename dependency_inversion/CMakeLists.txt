cmake_minimum_required(VERSION 3.10)
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(DesingPattern)
add_executable(DesignPattern main.cpp)
