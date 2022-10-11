cmake_minimum_required(VERSION 3.23)
project(
    MazeNew
)

set(CMAKE_CXX_STANDARD 14)
set(
    SOURCE_FILES
    src/main.cpp
)

set(build_dir "MazeNew")

set(EXECUTABLE_OUTPUT_PATH ${build_dir})

add_executable(MazeNew ${SOURCE_FILES})
