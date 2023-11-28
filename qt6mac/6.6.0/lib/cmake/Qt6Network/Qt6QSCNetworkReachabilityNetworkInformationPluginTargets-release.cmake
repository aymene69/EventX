#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QSCNetworkReachabilityNetworkInformationPlugin" for configuration "Release"
set_property(TARGET Qt6::QSCNetworkReachabilityNetworkInformationPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QSCNetworkReachabilityNetworkInformationPlugin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;OBJCXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./plugins/networkinformation/libqscnetworkreachability.a"
  )

list(APPEND _cmake_import_check_targets Qt6::QSCNetworkReachabilityNetworkInformationPlugin )
list(APPEND _cmake_import_check_files_for_Qt6::QSCNetworkReachabilityNetworkInformationPlugin "${_IMPORT_PREFIX}/./plugins/networkinformation/libqscnetworkreachability.a" )

# Import target "Qt6::QSCNetworkReachabilityNetworkInformationPlugin_init" for configuration "Release"
set_property(TARGET Qt6::QSCNetworkReachabilityNetworkInformationPlugin_init APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QSCNetworkReachabilityNetworkInformationPlugin_init PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/./plugins/networkinformation/objects-Release/QSCNetworkReachabilityNetworkInformationPlugin_init/QSCNetworkReachabilityNetworkInformationPlugin_init.cpp.o"
  )

list(APPEND _cmake_import_check_targets Qt6::QSCNetworkReachabilityNetworkInformationPlugin_init )
list(APPEND _cmake_import_check_files_for_Qt6::QSCNetworkReachabilityNetworkInformationPlugin_init "${_IMPORT_PREFIX}/./plugins/networkinformation/objects-Release/QSCNetworkReachabilityNetworkInformationPlugin_init/QSCNetworkReachabilityNetworkInformationPlugin_init.cpp.o" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
