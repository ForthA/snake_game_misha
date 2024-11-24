cmake_minimum_required(VERSION 3.30)
project(snake_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(snake_game main.cpp
        Game.cpp
        Game.h)
