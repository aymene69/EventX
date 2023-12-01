#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Widgets" for configuration "Release"
set_property(TARGET Qt6::Widgets APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Widgets PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Qt6Widgets.lib"
  )

list(APPEND _cmake_import_check_targets Qt6::Widgets )
list(APPEND _cmake_import_check_files_for_Qt6::Widgets "${_IMPORT_PREFIX}/lib/Qt6Widgets.lib" )

# Import target "Qt6::Widgets_resources_1" for configuration "Release"
set_property(TARGET Qt6::Widgets_resources_1 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Widgets_resources_1 PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/lib/objects-Release/Widgets_resources_1/.rcc/qrc_qstyle.cpp.obj"
  )

list(APPEND _cmake_import_check_targets Qt6::Widgets_resources_1 )
list(APPEND _cmake_import_check_files_for_Qt6::Widgets_resources_1 "${_IMPORT_PREFIX}/lib/objects-Release/Widgets_resources_1/.rcc/qrc_qstyle.cpp.obj" )

# Import target "Qt6::Widgets_resources_2" for configuration "Release"
set_property(TARGET Qt6::Widgets_resources_2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Widgets_resources_2 PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/lib/objects-Release/Widgets_resources_2/.rcc/qrc_qstyle1.cpp.obj"
  )

list(APPEND _cmake_import_check_targets Qt6::Widgets_resources_2 )
list(APPEND _cmake_import_check_files_for_Qt6::Widgets_resources_2 "${_IMPORT_PREFIX}/lib/objects-Release/Widgets_resources_2/.rcc/qrc_qstyle1.cpp.obj" )

# Import target "Qt6::Widgets_resources_3" for configuration "Release"
set_property(TARGET Qt6::Widgets_resources_3 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Widgets_resources_3 PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/lib/objects-Release/Widgets_resources_3/.rcc/qrc_qmessagebox.cpp.obj"
  )

list(APPEND _cmake_import_check_targets Qt6::Widgets_resources_3 )
list(APPEND _cmake_import_check_files_for_Qt6::Widgets_resources_3 "${_IMPORT_PREFIX}/lib/objects-Release/Widgets_resources_3/.rcc/qrc_qmessagebox.cpp.obj" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
