cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial)
set(CMAKE_CXX_STANDARD 17)
# add boost dependency
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

# add the executable
add_executable(Tutorial main.cpp)
