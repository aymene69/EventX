#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::BundledLibjpeg12bits" for configuration "Release"
set_property(TARGET Qt6::BundledLibjpeg12bits APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::BundledLibjpeg12bits PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libQt6BundledLibjpeg12bits.a"
  )

list(APPEND _cmake_import_check_targets Qt6::BundledLibjpeg12bits )
list(APPEND _cmake_import_check_files_for_Qt6::BundledLibjpeg12bits "${_IMPORT_PREFIX}/lib/libQt6BundledLibjpeg12bits.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
