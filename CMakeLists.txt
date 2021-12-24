cmake_minimum_required(VERSION 3.20)
project(window_life)

set(CMAKE_CXX_STANDARD 20)

#find graphic lib
find_package(SFML 2.5.1 COMPONENTS graphics window REQUIRED)
add_executable(window_life life.h life.cpp main.cpp Game.cpp Game.h Game.cpp Game.h main.cpp)

target_link_libraries(window_life PUBLIC sfml-graphics sfml-window)