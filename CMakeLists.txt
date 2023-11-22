cmake_minimum_required(VERSION 3.26)
project(EventX)

# Configuration C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/aymenebelmeguenai/Qt/6.6.0/macos/lib/cmake/Qt6")
set(NLOHMANN_JSON_INCLUDE_DIR "nlohmann")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# Liste des fichiers source
set(SOURCES
        src/Event.cpp
        src/Participant.cpp
        src/Stand.cpp
        src/Manager.cpp
        src/GestionEvenement.cpp
        src/GestionParticipant.cpp
        src/FonctionsJson.cpp
        src/FonctionsDemarrage.cpp
        src/main.cpp
)

# Liste des fichiers d'en-tête
set(HEADERS
        include/Event.hpp
        include/Participant.hpp
        include/Stand.hpp
        include/Manager.hpp
        include/GestionEvenement.hpp
        include/GestionParticipant.hpp
        include/FonctionsJson.hpp
        include/FonctionsDemarrage.hpp
)

# Ajout de l'exécutable
add_executable(EventX ${SOURCES} ${HEADERS})

# Configurer les dossiers d'inclusion
target_include_directories(EventX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${NLOHMANN_JSON_INCLUDE_DIR})

# Liaison des bibliothèques Qt
target_link_libraries(EventX
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
