cmake_minimum_required(VERSION 3.9)
project(nibbler)

set(CMAKE_CXX_STANDARD 11)

add_executable(nibbler
        project/incl/nibbler.h
        project/srcs/main.c)
