#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QDarwinMicrophonePermissionPlugin" for configuration "Release"
set_property(TARGET Qt6::QDarwinMicrophonePermissionPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QDarwinMicrophonePermissionPlugin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;OBJCXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./plugins/permissions/libqdarwinmicrophonepermission.a"
  )

list(APPEND _cmake_import_check_targets Qt6::QDarwinMicrophonePermissionPlugin )
list(APPEND _cmake_import_check_files_for_Qt6::QDarwinMicrophonePermissionPlugin "${_IMPORT_PREFIX}/./plugins/permissions/libqdarwinmicrophonepermission.a" )

# Import target "Qt6::QDarwinMicrophonePermissionPlugin_init" for configuration "Release"
set_property(TARGET Qt6::QDarwinMicrophonePermissionPlugin_init APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QDarwinMicrophonePermissionPlugin_init PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/./plugins/permissions/objects-Release/QDarwinMicrophonePermissionPlugin_init/QDarwinMicrophonePermissionPlugin_init.cpp.o"
  )

list(APPEND _cmake_import_check_targets Qt6::QDarwinMicrophonePermissionPlugin_init )
list(APPEND _cmake_import_check_files_for_Qt6::QDarwinMicrophonePermissionPlugin_init "${_IMPORT_PREFIX}/./plugins/permissions/objects-Release/QDarwinMicrophonePermissionPlugin_init/QDarwinMicrophonePermissionPlugin_init.cpp.o" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
