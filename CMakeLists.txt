cmake_minimum_required(VERSION 3.26)
project(EventX)
if(WIN32)
    add_definitions(-DQ_OS_WIN)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(NLOHMANN_JSON_INCLUDE_DIR "nlohmann")

if(WIN32)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED STATIC)
else()
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
endif()

# Liste des fichiers source
set(SOURCES
        src/MainWindow.cpp
        src/Event.cpp
        src/Participant.cpp
        src/Stand.cpp
        src/Manager.cpp
        src/GestionEvenement.cpp
        src/GestionParticipant.cpp
        src/GestionStand.cpp
        src/GestionManager.cpp
        src/FonctionsJson.cpp
        src/FonctionsDemarrage.cpp
        src/main.cpp
)

# Liste des fichiers d'en-tête
set(HEADERS
        include/MainWindow.hpp
        include/Event.hpp
        include/Participant.hpp
        include/Stand.hpp
        include/Manager.hpp
        include/GestionEvenement.hpp
        include/GestionParticipant.hpp
        include/GestionStand.hpp
        include/GestionManager.hpp
        include/FonctionsJson.hpp
        include/FonctionsDemarrage.hpp
)

# Ajout de l'exécutable
IF (WIN32)
    add_executable(EventX WIN32 ${SOURCES} ${HEADERS})
ELSE ()
    add_executable(EventX ${SOURCES} ${HEADERS})
ENDIF ()
# Configurer les dossiers d'inclusion
target_include_directories(EventX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${NLOHMANN_JSON_INCLUDE_DIR})

# Liaison des bibliothèques Qt
target_link_libraries(EventX Qt6::Core Qt6::Gui Qt6::Widgets)