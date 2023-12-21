cmake_minimum_required(VERSION 3.26)
project(OOPV2)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOPV2 main.cpp
        Administrator.cpp
        Administrator.h
        Publication.cpp
        Publication.h
        Users.cpp
        Users.h
        Order.cpp
        Order.h
)
