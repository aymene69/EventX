#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Protobuf" for configuration "Release"
set_property(TARGET Qt6::Protobuf APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Protobuf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libQt6Protobuf.a"
  )

list(APPEND _cmake_import_check_targets Qt6::Protobuf )
list(APPEND _cmake_import_check_files_for_Qt6::Protobuf "${_IMPORT_PREFIX}/lib/libQt6Protobuf.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)