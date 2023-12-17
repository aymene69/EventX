if (CMAKE_VERSION VERSION_LESS 3.1.0)
    message(FATAL_ERROR "Qt 5 PositioningQuick module requires at least CMake version 3.1.0")
endif()

get_filename_component(_qt5PositioningQuick_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

# For backwards compatibility only. Use Qt5PositioningQuick_VERSION instead.
set(Qt5PositioningQuick_VERSION_STRING 5.15.2)

set(Qt5PositioningQuick_LIBRARIES Qt5::PositioningQuick)

macro(_qt5_PositioningQuick_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The imported target \"Qt5::PositioningQuick\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
endmacro()


macro(_populate_PositioningQuick_target_properties Configuration LIB_LOCATION IMPLIB_LOCATION
      IsDebugAndRelease)
    set_property(TARGET Qt5::PositioningQuick APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

    set(imported_location "${_qt5PositioningQuick_install_prefix}/lib/${LIB_LOCATION}")
    _qt5_PositioningQuick_check_file_exists(${imported_location})
    set(_deps
        ${_Qt5PositioningQuick_LIB_DEPENDENCIES}
    )
    set(_static_deps
    )

    set_target_properties(Qt5::PositioningQuick PROPERTIES
        "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        # For backward compatibility with CMake < 2.8.12
        "IMPORTED_LINK_INTERFACE_LIBRARIES_${Configuration}" "${_deps};${_static_deps}"
    )
    set_property(TARGET Qt5::PositioningQuick APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 "${_deps}"
    )


endmacro()

if (NOT TARGET Qt5::PositioningQuick)

    set(_Qt5PositioningQuick_OWN_INCLUDE_DIRS
      "${_qt5PositioningQuick_install_prefix}/lib/QtPositioningQuick.framework"
      "${_qt5PositioningQuick_install_prefix}/lib/QtPositioningQuick.framework/Headers"
    )
    set(Qt5PositioningQuick_PRIVATE_INCLUDE_DIRS
        "${_qt5PositioningQuick_install_prefix}/lib/QtPositioningQuick.framework/Versions/5/Headers/5.15.2/"
        "${_qt5PositioningQuick_install_prefix}/lib/QtPositioningQuick.framework/Versions/5/Headers/5.15.2/QtPositioningQuick"
    )

    foreach(_dir ${_Qt5PositioningQuick_OWN_INCLUDE_DIRS})
        _qt5_PositioningQuick_check_file_exists(${_dir})
    endforeach()


    set(Qt5PositioningQuick_INCLUDE_DIRS ${_Qt5PositioningQuick_OWN_INCLUDE_DIRS})

    set(Qt5PositioningQuick_DEFINITIONS -DQT_POSITIONINGQUICK_LIB)
    set(Qt5PositioningQuick_COMPILE_DEFINITIONS QT_POSITIONINGQUICK_LIB)
    set(_Qt5PositioningQuick_MODULE_DEPENDENCIES "Positioning;Quick;Qml;Core")


    set(Qt5PositioningQuick_OWN_PRIVATE_INCLUDE_DIRS ${Qt5PositioningQuick_PRIVATE_INCLUDE_DIRS})

    set(_Qt5PositioningQuick_FIND_DEPENDENCIES_REQUIRED)
    if (Qt5PositioningQuick_FIND_REQUIRED)
        set(_Qt5PositioningQuick_FIND_DEPENDENCIES_REQUIRED REQUIRED)
    endif()
    set(_Qt5PositioningQuick_FIND_DEPENDENCIES_QUIET)
    if (Qt5PositioningQuick_FIND_QUIETLY)
        set(_Qt5PositioningQuick_DEPENDENCIES_FIND_QUIET QUIET)
    endif()
    set(_Qt5PositioningQuick_FIND_VERSION_EXACT)
    if (Qt5PositioningQuick_FIND_VERSION_EXACT)
        set(_Qt5PositioningQuick_FIND_VERSION_EXACT EXACT)
    endif()

    set(Qt5PositioningQuick_EXECUTABLE_COMPILE_FLAGS "")

    foreach(_module_dep ${_Qt5PositioningQuick_MODULE_DEPENDENCIES})
        if (NOT Qt5${_module_dep}_FOUND)
            find_package(Qt5${_module_dep}
                5.15.2 ${_Qt5PositioningQuick_FIND_VERSION_EXACT}
                ${_Qt5PositioningQuick_DEPENDENCIES_FIND_QUIET}
                ${_Qt5PositioningQuick_FIND_DEPENDENCIES_REQUIRED}
                PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH
            )
        endif()

        if (NOT Qt5${_module_dep}_FOUND)
            set(Qt5PositioningQuick_FOUND False)
            return()
        endif()

        list(APPEND Qt5PositioningQuick_INCLUDE_DIRS "${Qt5${_module_dep}_INCLUDE_DIRS}")
        list(APPEND Qt5PositioningQuick_PRIVATE_INCLUDE_DIRS "${Qt5${_module_dep}_PRIVATE_INCLUDE_DIRS}")
        list(APPEND Qt5PositioningQuick_DEFINITIONS ${Qt5${_module_dep}_DEFINITIONS})
        list(APPEND Qt5PositioningQuick_COMPILE_DEFINITIONS ${Qt5${_module_dep}_COMPILE_DEFINITIONS})
        list(APPEND Qt5PositioningQuick_EXECUTABLE_COMPILE_FLAGS ${Qt5${_module_dep}_EXECUTABLE_COMPILE_FLAGS})
    endforeach()
    list(REMOVE_DUPLICATES Qt5PositioningQuick_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5PositioningQuick_PRIVATE_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5PositioningQuick_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5PositioningQuick_COMPILE_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5PositioningQuick_EXECUTABLE_COMPILE_FLAGS)

    # It can happen that the same FooConfig.cmake file is included when calling find_package()
    # on some Qt component. An example of that is when using a Qt static build with auto inclusion
    # of plugins:
    #
    # Qt5WidgetsConfig.cmake -> Qt5GuiConfig.cmake -> Qt5Gui_QSvgIconPlugin.cmake ->
    # Qt5SvgConfig.cmake -> Qt5WidgetsConfig.cmake ->
    # finish processing of second Qt5WidgetsConfig.cmake ->
    # return to first Qt5WidgetsConfig.cmake ->
    # add_library cannot create imported target Qt5::Widgets.
    #
    # Make sure to return early in the original Config inclusion, because the target has already
    # been defined as part of the second inclusion.
    if(TARGET Qt5::PositioningQuick)
        return()
    endif()

    set(_Qt5PositioningQuick_LIB_DEPENDENCIES "Qt5::Positioning;Qt5::Quick;Qt5::Qml;Qt5::Core")


    add_library(Qt5::PositioningQuick SHARED IMPORTED)

    set_property(TARGET Qt5::PositioningQuick PROPERTY FRAMEWORK 1)

    set_property(TARGET Qt5::PositioningQuick PROPERTY
      INTERFACE_INCLUDE_DIRECTORIES ${_Qt5PositioningQuick_OWN_INCLUDE_DIRS})
    set_property(TARGET Qt5::PositioningQuick PROPERTY
      INTERFACE_COMPILE_DEFINITIONS QT_POSITIONINGQUICK_LIB)

    set_property(TARGET Qt5::PositioningQuick PROPERTY INTERFACE_QT_ENABLED_FEATURES )
    set_property(TARGET Qt5::PositioningQuick PROPERTY INTERFACE_QT_DISABLED_FEATURES )

    # Qt 6 forward compatible properties.
    set_property(TARGET Qt5::PositioningQuick
                 PROPERTY QT_ENABLED_PUBLIC_FEATURES
                 )
    set_property(TARGET Qt5::PositioningQuick
                 PROPERTY QT_DISABLED_PUBLIC_FEATURES
                 )
    set_property(TARGET Qt5::PositioningQuick
                 PROPERTY QT_ENABLED_PRIVATE_FEATURES
                 )
    set_property(TARGET Qt5::PositioningQuick
                 PROPERTY QT_DISABLED_PRIVATE_FEATURES
                 )

    set_property(TARGET Qt5::PositioningQuick PROPERTY INTERFACE_QT_PLUGIN_TYPES "")

    set(_Qt5PositioningQuick_PRIVATE_DIRS_EXIST TRUE)
    foreach (_Qt5PositioningQuick_PRIVATE_DIR ${Qt5PositioningQuick_OWN_PRIVATE_INCLUDE_DIRS})
        if (NOT EXISTS ${_Qt5PositioningQuick_PRIVATE_DIR})
            set(_Qt5PositioningQuick_PRIVATE_DIRS_EXIST FALSE)
        endif()
    endforeach()

    if (_Qt5PositioningQuick_PRIVATE_DIRS_EXIST)
        add_library(Qt5::PositioningQuickPrivate INTERFACE IMPORTED)
        set_property(TARGET Qt5::PositioningQuickPrivate PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Qt5PositioningQuick_OWN_PRIVATE_INCLUDE_DIRS}
        )
        set(_Qt5PositioningQuick_PRIVATEDEPS)
        foreach(dep ${_Qt5PositioningQuick_LIB_DEPENDENCIES})
            if (TARGET ${dep}Private)
                list(APPEND _Qt5PositioningQuick_PRIVATEDEPS ${dep}Private)
            endif()
        endforeach()
        set_property(TARGET Qt5::PositioningQuickPrivate PROPERTY
            INTERFACE_LINK_LIBRARIES Qt5::PositioningQuick ${_Qt5PositioningQuick_PRIVATEDEPS}
        )

        # Add a versionless target, for compatibility with Qt6.
        if(NOT "${QT_NO_CREATE_VERSIONLESS_TARGETS}" AND NOT TARGET Qt::PositioningQuickPrivate)
            add_library(Qt::PositioningQuickPrivate INTERFACE IMPORTED)
            set_target_properties(Qt::PositioningQuickPrivate PROPERTIES
                INTERFACE_LINK_LIBRARIES "Qt5::PositioningQuickPrivate"
            )
        endif()
    endif()

    _populate_PositioningQuick_target_properties(RELEASE "QtPositioningQuick.framework/QtPositioningQuick" "" FALSE)




    # In Qt 5.15 the glob pattern was relaxed to also catch plugins not literally named Plugin.
    # Define QT5_STRICT_PLUGIN_GLOB or ModuleName_STRICT_PLUGIN_GLOB to revert to old behavior.
    if (QT5_STRICT_PLUGIN_GLOB OR Qt5PositioningQuick_STRICT_PLUGIN_GLOB)
        file(GLOB pluginTargets "${CMAKE_CURRENT_LIST_DIR}/Qt5PositioningQuick_*Plugin.cmake")
    else()
        file(GLOB pluginTargets "${CMAKE_CURRENT_LIST_DIR}/Qt5PositioningQuick_*.cmake")
    endif()

    macro(_populate_PositioningQuick_plugin_properties Plugin Configuration PLUGIN_LOCATION
          IsDebugAndRelease)
        set_property(TARGET Qt5::${Plugin} APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

        set(imported_location "${_qt5PositioningQuick_install_prefix}/plugins/${PLUGIN_LOCATION}")
        _qt5_PositioningQuick_check_file_exists(${imported_location})
        set_target_properties(Qt5::${Plugin} PROPERTIES
            "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        )

    endmacro()

    if (pluginTargets)
        foreach(pluginTarget ${pluginTargets})
            include(${pluginTarget})
        endforeach()
    endif()



    _qt5_PositioningQuick_check_file_exists("${CMAKE_CURRENT_LIST_DIR}/Qt5PositioningQuickConfigVersion.cmake")
endif()

# Add a versionless target, for compatibility with Qt6.
if(NOT "${QT_NO_CREATE_VERSIONLESS_TARGETS}" AND TARGET Qt5::PositioningQuick AND NOT TARGET Qt::PositioningQuick)
    add_library(Qt::PositioningQuick INTERFACE IMPORTED)
    set_target_properties(Qt::PositioningQuick PROPERTIES
        INTERFACE_LINK_LIBRARIES "Qt5::PositioningQuick"
    )
endif()
