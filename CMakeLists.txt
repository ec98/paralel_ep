cmake_minimum_required(VERSION 3.28)
project(paralel_ep)

set(CMAKE_CXX_STANDARD 17)
find_package(fmt)
find_package(SFML)

add_executable(paralel_ep main.cpp)
target_link_libraries(paralel_ep fmt::fmt sfml::sfml)