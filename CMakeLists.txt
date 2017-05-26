cmake_minimum_required(VERSION 2.8)
project(keyboard)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        maintest.cpp Keyboard.cpp Keyboard.h)

add_executable(maintest ${SOURCE_FILES})