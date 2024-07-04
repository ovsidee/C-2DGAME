cmake_minimum_required(VERSION 3.27)
project(CPlusPlusPR)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

# Fetch SFML
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)
FetchContent_MakeAvailable(SFML)

# Fetch fmt
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        10.2.1
)
FetchContent_MakeAvailable(fmt)

add_executable(CPlusPlusPR main.cpp
        Game.h
        Game.cpp
        Player.h
        Player.cpp
        Button.cpp
        Button.h
        MainMenu.cpp
        MainMenu.h
        Enemy.h
        Wizard.cpp
        Wizard.h
        Bat.cpp
        Bat.h
        Magician.cpp
        Magician.h
        NightBorn.cpp
        NightBorn.h
        Boss.cpp
        Boss.h
        Obstacles.cpp
        Obstacles.h
        Items.cpp
        Items.h
        ItemType.h
)

# Link the libraries
target_link_libraries(CPlusPlusPR PRIVATE sfml-graphics fmt::fmt)