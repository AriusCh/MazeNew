cmake_minimum_required(VERSION 3.23)
project(
        MazeNew
)

set(CMAKE_CXX_STANDARD 20)
set(
        SOURCE_FILES
        src/main.cpp
        src/game.cpp src/game.h
        src/screen.cpp src/screen.h
        src/dungeon.cpp src/dungeon.h
        src/cell.cpp src/cell.h
        src/wall.cpp src/wall.h
        src/ground.cpp src/ground.h)

set(build_dir "MazeNew")

set(EXECUTABLE_OUTPUT_PATH ${build_dir})

add_executable(MazeNew ${SOURCE_FILES})
