cmake_minimum_required(VERSION 3.23)
project(
        MazeNew
)

set(CMAKE_CXX_STANDARD 20)
set(
        SOURCE_FILES
        src/main.cpp
        src/game.cpp src/game.h
        src/terminal.cpp src/terminal.h
        src/dungeon.cpp src/dungeon.h
        src/cell.cpp src/cell.h
        src/player.cpp src/player.h
        src/character.cpp src/character.h
        src/curses.h src/terrain.cpp src/terrain.h src/object.cpp src/object.h)

set(build_dir "MazeNew")

set(EXECUTABLE_OUTPUT_PATH ${build_dir})

add_executable(MazeNew ${SOURCE_FILES})

if (MSYS OR MINGW)
    message(STATUS "NOTE: Configuring build for Windows release...")
    find_library(PDCURSES pdcurses lib)
    include_directories(include)
    target_link_libraries(MazeNew ${PDCURSES})
else ()
    message(STATUS "NOTE: Configuring build for macOS/Linux release...")
    set(CURSES_NEED_NCURSES TRUE)
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries(MazeNew ${CURSES_LIBRARIES})
endif ()
