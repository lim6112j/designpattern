# [how to add boost library for emacs clangd language server](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html) 
* install boost library

``` sh
brew install boost
```

* make file : CMakeLists.txt

``` cmake
cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial)

# add boost dependency
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

# add the executable
add_executable(Tutorial tutorial.cpp)
```

* run 

``` cmake
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

* compile_commands.json will be made .
* clangd language server will recognize #include <boost>


# build and run

``` sh
mkdir build_dir
cd build_dir
cmake ../src_dir
cmake --build .
```
* run executable

``` sh
Tutorial
```

