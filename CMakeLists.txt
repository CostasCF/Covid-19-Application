cmake_minimum_required(VERSION 3.16)
project(Covid_19_Application)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Covid_19_Application
    LinkedList.cpp
    LinkedList.h
    main.cpp
    User.h)
