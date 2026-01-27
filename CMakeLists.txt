cmake_minimum_required(VERSION 3.10)

project(tp6_note VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sources
set(SOURCES
    main.cpp
    Case.cpp
    Cercle.cpp
    Humain.cpp
    Jeu.cpp
    Joueur.cpp
    Machine.cpp
    Plateau.cpp
)

add_executable(tp6 ${SOURCES})

target_include_directories(tp6 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    target_compile_options(tp6 PRIVATE /W4 /permissive-)
else()
    target_compile_options(tp6 PRIVATE -Wall -Wextra -Wpedantic)
endif()
