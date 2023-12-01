#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QCocoaIntegrationPlugin" for configuration "Release"
set_property(TARGET Qt6::QCocoaIntegrationPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QCocoaIntegrationPlugin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;OBJCXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./plugins/platforms/libqcocoa.a"
  )

list(APPEND _cmake_import_check_targets Qt6::QCocoaIntegrationPlugin )
list(APPEND _cmake_import_check_files_for_Qt6::QCocoaIntegrationPlugin "${_IMPORT_PREFIX}/./plugins/platforms/libqcocoa.a" )

# Import target "Qt6::QCocoaIntegrationPlugin_init" for configuration "Release"
set_property(TARGET Qt6::QCocoaIntegrationPlugin_init APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QCocoaIntegrationPlugin_init PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/./plugins/platforms/objects-Release/QCocoaIntegrationPlugin_init/QCocoaIntegrationPlugin_init.cpp.o"
  )

list(APPEND _cmake_import_check_targets Qt6::QCocoaIntegrationPlugin_init )
list(APPEND _cmake_import_check_files_for_Qt6::QCocoaIntegrationPlugin_init "${_IMPORT_PREFIX}/./plugins/platforms/objects-Release/QCocoaIntegrationPlugin_init/QCocoaIntegrationPlugin_init.cpp.o" )

# Import target "Qt6::QCocoaIntegrationPlugin_resources_1" for configuration "Release"
set_property(TARGET Qt6::QCocoaIntegrationPlugin_resources_1 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QCocoaIntegrationPlugin_resources_1 PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/lib/objects-Release/QCocoaIntegrationPlugin_resources_1/.rcc/qrc_qcocoaresources.cpp.o"
  )

list(APPEND _cmake_import_check_targets Qt6::QCocoaIntegrationPlugin_resources_1 )
list(APPEND _cmake_import_check_files_for_Qt6::QCocoaIntegrationPlugin_resources_1 "${_IMPORT_PREFIX}/lib/objects-Release/QCocoaIntegrationPlugin_resources_1/.rcc/qrc_qcocoaresources.cpp.o" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
