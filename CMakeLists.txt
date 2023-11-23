cmake_minimum_required(VERSION 3.26)
project(EventX)

# Configuration C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Recherche des packages Qt
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
set(NLOHMANN_JSON_INCLUDE_DIR "nlohmann")

# Liste des fichiers source
set(SOURCES
        src/MainWindow.cpp
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
        include/MainWindow.hpp
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
target_link_libraries(EventX Qt6::Core Qt6::Gui Qt6::Widgets)

# Traitement spécifique à Windows
if (WIN32)
    # Remplacez le chemin avec le chemin vers votre installation de Qt sur Windows
    set(CMAKE_PREFIX_PATH "C:/chemin/vers/Qt/6.6.0/msvc2019_64/lib/cmake/Qt6")
    # Ajoutez ici d'autres configurations spécifiques à Windows si nécessaire
endif()

# Traitement spécifique à Mac
if (APPLE)
    # Remplacez le chemin avec le chemin vers votre installation de Qt sur Mac
    set(CMAKE_PREFIX_PATH "/Users/aymenebelmeguenai/Qt/6.6.0/macos/lib/cmake/Qt6")
    # Ajoutez ici d'autres configurations spécifiques à Mac si nécessaire
endif()
