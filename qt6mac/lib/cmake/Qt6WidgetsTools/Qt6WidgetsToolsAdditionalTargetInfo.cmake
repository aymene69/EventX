# Additional target information for Qt6WidgetsTools
if(NOT DEFINED QT_DEFAULT_IMPORT_CONFIGURATION)
    set(QT_DEFAULT_IMPORT_CONFIGURATION RELEASE)
endif()
get_target_property(_qt_imported_location Qt6::uic IMPORTED_LOCATION_RELEASE)
get_target_property(_qt_imported_location_default Qt6::uic IMPORTED_LOCATION_${QT_DEFAULT_IMPORT_CONFIGURATION})

# Import target "Qt6::uic" for configuration "RelWithDebInfo"
set_property(TARGET Qt6::uic APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)

if(_qt_imported_location)
    set_property(TARGET Qt6::uic PROPERTY IMPORTED_LOCATION_RELWITHDEBINFO "${_qt_imported_location}")
endif()

# Import target "Qt6::uic" for configuration "MinSizeRel"
set_property(TARGET Qt6::uic APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)

if(_qt_imported_location)
    set_property(TARGET Qt6::uic PROPERTY IMPORTED_LOCATION_MINSIZEREL "${_qt_imported_location}")
endif()

# Default configuration
if(_qt_imported_location_default)
    set_property(TARGET Qt6::uic PROPERTY IMPORTED_LOCATION "${_qt_imported_location_default}")
endif()

unset(_qt_imported_location)
unset(_qt_imported_location_default)
unset(_qt_imported_soname)
unset(_qt_imported_soname_default)
unset(_qt_imported_configs)
