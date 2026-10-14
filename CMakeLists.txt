cmake_minimum_required(VERSION 4.3)
project(HUITA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HUITA
        App.cpp
        App.h
        main.cpp
        Contracts.cpp
        Contracts.h
        GameData.cpp
        GameData.h
        Part.cpp
        Part.h
        Engine.cpp
        Engine.h
        Payload.cpp
        Payload.h
)
