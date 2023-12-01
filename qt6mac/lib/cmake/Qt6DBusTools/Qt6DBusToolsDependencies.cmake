# Find "ModuleTools" dependencies, which are other ModuleTools packages.
set(Qt6DBusTools_FOUND FALSE)
set(__qt_DBusTools_tool_deps "Qt6CoreTools\;6.6.1")
foreach(__qt_DBusTools_target_dep ${__qt_DBusTools_tool_deps})
    list(GET __qt_DBusTools_target_dep 0 __qt_DBusTools_pkg)
    list(GET __qt_DBusTools_target_dep 1 __qt_DBusTools_version)

    if (NOT ${__qt_DBusTools_pkg}_FOUND)
        find_dependency(${__qt_DBusTools_pkg} ${__qt_DBusTools_version})
    endif()
endforeach()

set(Qt6DBusTools_FOUND TRUE)
