#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::BundledZLIB" for configuration "Release"
set_property(TARGET Qt6::BundledZLIB APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::BundledZLIB PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Qt6BundledZLIB.lib"
  )

list(APPEND _cmake_import_check_targets Qt6::BundledZLIB )
list(APPEND _cmake_import_check_files_for_Qt6::BundledZLIB "${_IMPORT_PREFIX}/lib/Qt6BundledZLIB.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
