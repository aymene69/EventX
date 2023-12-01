#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QSecureTransportBackendPlugin" for configuration "Release"
set_property(TARGET Qt6::QSecureTransportBackendPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QSecureTransportBackendPlugin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./plugins/tls/libqsecuretransportbackend.a"
  )

list(APPEND _cmake_import_check_targets Qt6::QSecureTransportBackendPlugin )
list(APPEND _cmake_import_check_files_for_Qt6::QSecureTransportBackendPlugin "${_IMPORT_PREFIX}/./plugins/tls/libqsecuretransportbackend.a" )

# Import target "Qt6::QSecureTransportBackendPlugin_init" for configuration "Release"
set_property(TARGET Qt6::QSecureTransportBackendPlugin_init APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QSecureTransportBackendPlugin_init PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/./plugins/tls/objects-Release/QSecureTransportBackendPlugin_init/QSecureTransportBackendPlugin_init.cpp.o"
  )

list(APPEND _cmake_import_check_targets Qt6::QSecureTransportBackendPlugin_init )
list(APPEND _cmake_import_check_files_for_Qt6::QSecureTransportBackendPlugin_init "${_IMPORT_PREFIX}/./plugins/tls/objects-Release/QSecureTransportBackendPlugin_init/QSecureTransportBackendPlugin_init.cpp.o" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
