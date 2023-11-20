cmake_minimum_required(VERSION 3.12)
project(EventX)

# Configuration C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Liste des fichiers source
set(SOURCES
        src/Event.cpp
        src/Participant.cpp
        src/Stand.cpp
        src/Manager.cpp
        src/main.cpp
)

# Liste des fichiers d'en-tête
set(HEADERS
        include/Event.hpp
        include/Participant.hpp
        include/Stand.hpp
        include/Manager.hpp
)

# Ajout de l'exécutable
add_executable(EventX ${SOURCES} ${HEADERS})
# Configurer les dossiers d'inclusion
target_include_directories(EventX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
