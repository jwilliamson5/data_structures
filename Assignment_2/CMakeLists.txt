cmake_minimum_required(VERSION 3.9)
project(Assignment_2)

set(CMAKE_CXX_STANDARD 11)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(Assignment_2 main.cpp Pathfinder.cpp Pathfinder.h Node.cpp Node.h)