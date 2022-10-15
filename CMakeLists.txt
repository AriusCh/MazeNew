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

if ((MSYS OR MINGW) AND "$ENV{MINGW}" STREQUAL "")
    message(FATAL_ERROR "You must set the MINGW environment variable ('mingw64' or 'mingw32'). Example: MINGW=mingw64 cmake .")
    message(FATAL_ERROR "This will be the directory used for locating the ncurses library files.")
elseif ((MSYS OR MINGW) AND NOT "$ENV{MINGW}" STREQUAL "")
    message(STATUS "NOTE: Configuring build for Windows release...")

    # Make the ncurses library static
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -static -lpthread")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -static -lpthread")

    set(CURSES_INCLUDE_DIR "/$ENV{MINGW}/include/")
    set(CURSES_LIBRARIES "/$ENV{MINGW}/lib/libncurses.a")
else ()
    message(STATUS "NOTE: Configuring build for macOS/Linux release...")
    set(CURSES_NEED_NCURSES TRUE)
    find_package(Curses REQUIRED)
endif ()

include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(MazeNew ${CURSES_LIBRARIES})