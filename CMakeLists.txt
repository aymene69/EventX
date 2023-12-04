cmake_minimum_required(VERSION 3.24)
project(EventX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(WIN32)
    set(CMAKE_PREFIX_PATH "qt6win\\lib\\cmake")
else ()
    set(CMAKE_PREFIX_PATH "qt6mac/lib/cmake")
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()

set(NLOHMANN_JSON_INCLUDE_DIR "nlohmann")

find_package(Qt6 COMPONENTS
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
set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/assets/windows/ressources.rc")
add_executable(EventX WIN32 ${SOURCES} ${HEADERS} ${app_icon_resource_windows})

target_include_directories(EventX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${NLOHMANN_JSON_INCLUDE_DIR})

target_link_libraries(EventX Qt6::Core Qt6::Gui Qt6::Widgets)