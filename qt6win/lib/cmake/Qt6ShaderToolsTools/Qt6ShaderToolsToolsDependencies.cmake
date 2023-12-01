# Find "ModuleTools" dependencies, which are other ModuleTools packages.
set(Qt6ShaderToolsTools_FOUND FALSE)
set(__qt_ShaderToolsTools_tool_deps "")
foreach(__qt_ShaderToolsTools_target_dep ${__qt_ShaderToolsTools_tool_deps})
    list(GET __qt_ShaderToolsTools_target_dep 0 __qt_ShaderToolsTools_pkg)
    list(GET __qt_ShaderToolsTools_target_dep 1 __qt_ShaderToolsTools_version)

    if (NOT ${__qt_ShaderToolsTools_pkg}_FOUND)
        find_dependency(${__qt_ShaderToolsTools_pkg} ${__qt_ShaderToolsTools_version})
    endif()
endforeach()

set(Qt6ShaderToolsTools_FOUND TRUE)
