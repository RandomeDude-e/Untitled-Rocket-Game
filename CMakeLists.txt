    cmake_minimum_required(VERSION 4.3)

    project(HUITA)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
            Assembly.cpp
            Assembly.h
            Rocket.cpp
            Rocket.h
    )

    if(MINGW)
    target_link_options(HUITA PRIVATE
        -static-libgcc
        -static-libstdc++
    )
endif()
