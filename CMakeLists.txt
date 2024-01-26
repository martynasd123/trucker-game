cmake_minimum_required(VERSION 3.27)
project(trucker_game)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file(GLOB_RECURSE SUBDIR_SOURCES "src/*.cpp")
add_executable(trucker_game ${SUBDIR_SOURCES} main.cpp)