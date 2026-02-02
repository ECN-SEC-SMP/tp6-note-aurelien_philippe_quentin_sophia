cmake_minimum_required(VERSION 3.14)

project(tp6_note VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sources des classes
set(SOURCES
    src/Case.cpp
    src/Cercle.cpp
    src/Humain.cpp
    src/Jeu.cpp
    src/Joueur.cpp
    src/Machine.cpp
    src/Plateau.cpp
)

# --- EXECUTEUR PRINCIPAL ---
add_executable(tp6 src/main.cpp ${SOURCES})

# FIX 1: Ajout du slash manquant avant "lib"
target_include_directories(tp6 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# --- GOOGLE TEST ---
include(FetchContent)
FetchContent_Declare(
  gtest 
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  # FIX 3: Corrige le warning de timestamp
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE 
)
FetchContent_MakeAvailable(gtest)

# --- TESTS UNITAIRES ---
enable_testing()

# FIX 2: Suppression des ".." car CMakeLists est maintenant à la racine
file(GLOB TEST_FILES tests/*.cpp)

add_executable(unittests ${TEST_FILES} ${SOURCES})
target_link_libraries(unittests PRIVATE gtest_main)

# FIX 2: Suppression des ".." ici aussi
target_include_directories(unittests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include(GoogleTest)
gtest_discover_tests(unittests)

# Options de compilation 
if(MSVC)
    target_compile_options(tp6 PRIVATE /W4 /permissive-)
    target_compile_options(unittests PRIVATE /W4 /permissive-)
else()
    target_compile_options(tp6 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(unittests PRIVATE -Wall -Wextra -Wpedantic)
endif()