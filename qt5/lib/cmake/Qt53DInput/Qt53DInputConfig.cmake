if (CMAKE_VERSION VERSION_LESS 3.1.0)
    message(FATAL_ERROR "Qt 5 3DInput module requires at least CMake version 3.1.0")
endif()

get_filename_component(_qt53DInput_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

# For backwards compatibility only. Use Qt53DInput_VERSION instead.
set(Qt53DInput_VERSION_STRING 5.15.2)

set(Qt53DInput_LIBRARIES Qt5::3DInput)

macro(_qt5_3DInput_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The imported target \"Qt5::3DInput\" references the file
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


macro(_populate_3DInput_target_properties Configuration LIB_LOCATION IMPLIB_LOCATION
      IsDebugAndRelease)
    set_property(TARGET Qt5::3DInput APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

    set(imported_location "${_qt53DInput_install_prefix}/lib/${LIB_LOCATION}")
    _qt5_3DInput_check_file_exists(${imported_location})
    set(_deps
        ${_Qt53DInput_LIB_DEPENDENCIES}
    )
    set(_static_deps
    )

    set_target_properties(Qt5::3DInput PROPERTIES
        "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        # For backward compatibility with CMake < 2.8.12
        "IMPORTED_LINK_INTERFACE_LIBRARIES_${Configuration}" "${_deps};${_static_deps}"
    )
    set_property(TARGET Qt5::3DInput APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 "${_deps}"
    )


endmacro()

if (NOT TARGET Qt5::3DInput)

    set(_Qt53DInput_OWN_INCLUDE_DIRS
      "${_qt53DInput_install_prefix}/lib/Qt3DInput.framework"
      "${_qt53DInput_install_prefix}/lib/Qt3DInput.framework/Headers"
    )
    set(Qt53DInput_PRIVATE_INCLUDE_DIRS
        "${_qt53DInput_install_prefix}/lib/Qt3DInput.framework/Versions/5/Headers/5.15.2/"
        "${_qt53DInput_install_prefix}/lib/Qt3DInput.framework/Versions/5/Headers/5.15.2/Qt3DInput"
    )

    foreach(_dir ${_Qt53DInput_OWN_INCLUDE_DIRS})
        _qt5_3DInput_check_file_exists(${_dir})
    endforeach()


    set(Qt53DInput_INCLUDE_DIRS ${_Qt53DInput_OWN_INCLUDE_DIRS})

    set(Qt53DInput_DEFINITIONS -DQT_3DINPUT_LIB)
    set(Qt53DInput_COMPILE_DEFINITIONS QT_3DINPUT_LIB)
    set(_Qt53DInput_MODULE_DEPENDENCIES "3DCore;Gamepad;Gui;Core")


    set(Qt53DInput_OWN_PRIVATE_INCLUDE_DIRS ${Qt53DInput_PRIVATE_INCLUDE_DIRS})

    set(_Qt53DInput_FIND_DEPENDENCIES_REQUIRED)
    if (Qt53DInput_FIND_REQUIRED)
        set(_Qt53DInput_FIND_DEPENDENCIES_REQUIRED REQUIRED)
    endif()
    set(_Qt53DInput_FIND_DEPENDENCIES_QUIET)
    if (Qt53DInput_FIND_QUIETLY)
        set(_Qt53DInput_DEPENDENCIES_FIND_QUIET QUIET)
    endif()
    set(_Qt53DInput_FIND_VERSION_EXACT)
    if (Qt53DInput_FIND_VERSION_EXACT)
        set(_Qt53DInput_FIND_VERSION_EXACT EXACT)
    endif()

    set(Qt53DInput_EXECUTABLE_COMPILE_FLAGS "")

    foreach(_module_dep ${_Qt53DInput_MODULE_DEPENDENCIES})
        if (NOT Qt5${_module_dep}_FOUND)
            find_package(Qt5${_module_dep}
                5.15.2 ${_Qt53DInput_FIND_VERSION_EXACT}
                ${_Qt53DInput_DEPENDENCIES_FIND_QUIET}
                ${_Qt53DInput_FIND_DEPENDENCIES_REQUIRED}
                PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH
            )
        endif()

        if (NOT Qt5${_module_dep}_FOUND)
            set(Qt53DInput_FOUND False)
            return()
        endif()

        list(APPEND Qt53DInput_INCLUDE_DIRS "${Qt5${_module_dep}_INCLUDE_DIRS}")
        list(APPEND Qt53DInput_PRIVATE_INCLUDE_DIRS "${Qt5${_module_dep}_PRIVATE_INCLUDE_DIRS}")
        list(APPEND Qt53DInput_DEFINITIONS ${Qt5${_module_dep}_DEFINITIONS})
        list(APPEND Qt53DInput_COMPILE_DEFINITIONS ${Qt5${_module_dep}_COMPILE_DEFINITIONS})
        list(APPEND Qt53DInput_EXECUTABLE_COMPILE_FLAGS ${Qt5${_module_dep}_EXECUTABLE_COMPILE_FLAGS})
    endforeach()
    list(REMOVE_DUPLICATES Qt53DInput_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt53DInput_PRIVATE_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt53DInput_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt53DInput_COMPILE_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt53DInput_EXECUTABLE_COMPILE_FLAGS)

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
    if(TARGET Qt5::3DInput)
        return()
    endif()

    set(_Qt53DInput_LIB_DEPENDENCIES "Qt5::3DCore;Qt5::Gamepad;Qt5::Gui;Qt5::Core")


    add_library(Qt5::3DInput SHARED IMPORTED)

    set_property(TARGET Qt5::3DInput PROPERTY FRAMEWORK 1)

    set_property(TARGET Qt5::3DInput PROPERTY
      INTERFACE_INCLUDE_DIRECTORIES ${_Qt53DInput_OWN_INCLUDE_DIRS})
    set_property(TARGET Qt5::3DInput PROPERTY
      INTERFACE_COMPILE_DEFINITIONS QT_3DINPUT_LIB)

    set_property(TARGET Qt5::3DInput PROPERTY INTERFACE_QT_ENABLED_FEATURES )
    set_property(TARGET Qt5::3DInput PROPERTY INTERFACE_QT_DISABLED_FEATURES )

    # Qt 6 forward compatible properties.
    set_property(TARGET Qt5::3DInput
                 PROPERTY QT_ENABLED_PUBLIC_FEATURES
                 )
    set_property(TARGET Qt5::3DInput
                 PROPERTY QT_DISABLED_PUBLIC_FEATURES
                 )
    set_property(TARGET Qt5::3DInput
                 PROPERTY QT_ENABLED_PRIVATE_FEATURES
                 )
    set_property(TARGET Qt5::3DInput
                 PROPERTY QT_DISABLED_PRIVATE_FEATURES
                 )

    set_property(TARGET Qt5::3DInput PROPERTY INTERFACE_QT_PLUGIN_TYPES "3dinputdevices")

    set(_Qt53DInput_PRIVATE_DIRS_EXIST TRUE)
    foreach (_Qt53DInput_PRIVATE_DIR ${Qt53DInput_OWN_PRIVATE_INCLUDE_DIRS})
        if (NOT EXISTS ${_Qt53DInput_PRIVATE_DIR})
            set(_Qt53DInput_PRIVATE_DIRS_EXIST FALSE)
        endif()
    endforeach()

    if (_Qt53DInput_PRIVATE_DIRS_EXIST)
        add_library(Qt5::3DInputPrivate INTERFACE IMPORTED)
        set_property(TARGET Qt5::3DInputPrivate PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Qt53DInput_OWN_PRIVATE_INCLUDE_DIRS}
        )
        set(_Qt53DInput_PRIVATEDEPS)
        foreach(dep ${_Qt53DInput_LIB_DEPENDENCIES})
            if (TARGET ${dep}Private)
                list(APPEND _Qt53DInput_PRIVATEDEPS ${dep}Private)
            endif()
        endforeach()
        set_property(TARGET Qt5::3DInputPrivate PROPERTY
            INTERFACE_LINK_LIBRARIES Qt5::3DInput ${_Qt53DInput_PRIVATEDEPS}
        )

        # Add a versionless target, for compatibility with Qt6.
        if(NOT "${QT_NO_CREATE_VERSIONLESS_TARGETS}" AND NOT TARGET Qt::3DInputPrivate)
            add_library(Qt::3DInputPrivate INTERFACE IMPORTED)
            set_target_properties(Qt::3DInputPrivate PROPERTIES
                INTERFACE_LINK_LIBRARIES "Qt5::3DInputPrivate"
            )
        endif()
    endif()

    _populate_3DInput_target_properties(RELEASE "Qt3DInput.framework/Qt3DInput" "" FALSE)




    # In Qt 5.15 the glob pattern was relaxed to also catch plugins not literally named Plugin.
    # Define QT5_STRICT_PLUGIN_GLOB or ModuleName_STRICT_PLUGIN_GLOB to revert to old behavior.
    if (QT5_STRICT_PLUGIN_GLOB OR Qt53DInput_STRICT_PLUGIN_GLOB)
        file(GLOB pluginTargets "${CMAKE_CURRENT_LIST_DIR}/Qt53DInput_*Plugin.cmake")
    else()
        file(GLOB pluginTargets "${CMAKE_CURRENT_LIST_DIR}/Qt53DInput_*.cmake")
    endif()

    macro(_populate_3DInput_plugin_properties Plugin Configuration PLUGIN_LOCATION
          IsDebugAndRelease)
        set_property(TARGET Qt5::${Plugin} APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

        set(imported_location "${_qt53DInput_install_prefix}/plugins/${PLUGIN_LOCATION}")
        _qt5_3DInput_check_file_exists(${imported_location})
        set_target_properties(Qt5::${Plugin} PROPERTIES
            "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        )

    endmacro()

    if (pluginTargets)
        foreach(pluginTarget ${pluginTargets})
            include(${pluginTarget})
        endforeach()
    endif()



    _qt5_3DInput_check_file_exists("${CMAKE_CURRENT_LIST_DIR}/Qt53DInputConfigVersion.cmake")
endif()

# Add a versionless target, for compatibility with Qt6.
if(NOT "${QT_NO_CREATE_VERSIONLESS_TARGETS}" AND TARGET Qt5::3DInput AND NOT TARGET Qt::3DInput)
    add_library(Qt::3DInput INTERFACE IMPORTED)
    set_target_properties(Qt::3DInput PROPERTIES
        INTERFACE_LINK_LIBRARIES "Qt5::3DInput"
    )
endif()
