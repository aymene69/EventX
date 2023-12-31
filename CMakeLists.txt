cmake_minimum_required(VERSION 3.24)
project(EventX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "qt5")

set(NLOHMANN_JSON_INCLUDE_DIR "nlohmann")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

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

add_executable(EventX ${SOURCES} ${HEADERS})

target_include_directories(EventX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${NLOHMANN_JSON_INCLUDE_DIR})

target_link_libraries(EventX Qt5::Core Qt5::Gui Qt5::Widgets)
