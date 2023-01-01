cmake_minimum_required(VERSION 3.23)
project(FourthLab)

set(CMAKE_CXX_STANDARD 20)

add_executable(FourthServer main_server.cpp common.h check.hpp)
add_executable(FourthClient main_client.cpp common.h check.hpp)

