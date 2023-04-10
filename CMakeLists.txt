cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_CXX_STANDARD 11)

# STATIC stuff (Windows)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(BUILD_FOR_WIN TRUE)
endif()
option(STATIC_BUILD "Build a static binary." ${BUILD_FOR_WIN})

if (STATIC_BUILD)
        set(CMAKE_EXE_LINKER_FLAGS "-static")
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
        set(BUILD_SHARED_LIBS OFF)
endif()

set(SOURCES main.cpp cpp-terminal/terminal.cpp cpp-terminal/terminal_base.cpp tic-tac-toe/game.cpp tic-tac-toe/player.cpp tic-tac-toe/human.cpp tic-tac-toe/computer.cpp tic-tac-toe/field.cpp)

add_executable(ttt ${SOURCES})
