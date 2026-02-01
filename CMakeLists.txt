cmake_minimum_required(VERSION 3.10)
project(Otrio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(lib)

add_executable(tp6
    src/main.cpp
    src/Case.cpp
    src/Cercle.cpp
    src/Humain.cpp
    src/Jeu.cpp
    src/Joueur.cpp
    src/Machine.cpp
    src/Plateau.cpp
)

