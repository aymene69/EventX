#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::ExampleIconsPrivate" for configuration "Release"
set_property(TARGET Qt6::ExampleIconsPrivate APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::ExampleIconsPrivate PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libQt6ExampleIcons.a"
  )

list(APPEND _cmake_import_check_targets Qt6::ExampleIconsPrivate )
list(APPEND _cmake_import_check_files_for_Qt6::ExampleIconsPrivate "${_IMPORT_PREFIX}/lib/libQt6ExampleIcons.a" )

# Import target "Qt6::ExampleIconsPrivate_resources_1" for configuration "Release"
set_property(TARGET Qt6::ExampleIconsPrivate_resources_1 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::ExampleIconsPrivate_resources_1 PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/lib/objects-Release/ExampleIconsPrivate_resources_1/.rcc/qrc_example_icons.cpp.o"
  )

list(APPEND _cmake_import_check_targets Qt6::ExampleIconsPrivate_resources_1 )
list(APPEND _cmake_import_check_files_for_Qt6::ExampleIconsPrivate_resources_1 "${_IMPORT_PREFIX}/lib/objects-Release/ExampleIconsPrivate_resources_1/.rcc/qrc_example_icons.cpp.o" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
