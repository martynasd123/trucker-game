cmake_minimum_required(VERSION 3.27)
project(trucker_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(trucker_game main.cpp
        engine/EntityManager.cpp
        engine/EntityManager.h
        engine/ComponentManager.cpp
        engine/ComponentManager.h
        engine/ComponentArray.cpp
        engine/ComponentArray.h)
