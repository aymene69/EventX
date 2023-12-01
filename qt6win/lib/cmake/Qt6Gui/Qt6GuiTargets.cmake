# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8)
   message(FATAL_ERROR "CMake >= 2.8.0 required")
endif()
if(CMAKE_VERSION VERSION_LESS "2.8.3")
   message(FATAL_ERROR "CMake >= 2.8.3 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.8.3...3.25)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_cmake_targets_defined "")
set(_cmake_targets_not_defined "")
set(_cmake_expected_targets "")
foreach(_cmake_expected_target IN ITEMS Qt6::Gui Qt6::GuiPrivate Qt6::Gui_resources_1 Qt6::Gui_resources_2)
  list(APPEND _cmake_expected_targets "${_cmake_expected_target}")
  if(TARGET "${_cmake_expected_target}")
    list(APPEND _cmake_targets_defined "${_cmake_expected_target}")
  else()
    list(APPEND _cmake_targets_not_defined "${_cmake_expected_target}")
  endif()
endforeach()
unset(_cmake_expected_target)
if(_cmake_targets_defined STREQUAL _cmake_expected_targets)
  unset(_cmake_targets_defined)
  unset(_cmake_targets_not_defined)
  unset(_cmake_expected_targets)
  unset(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT _cmake_targets_defined STREQUAL "")
  string(REPLACE ";" ", " _cmake_targets_defined_text "${_cmake_targets_defined}")
  string(REPLACE ";" ", " _cmake_targets_not_defined_text "${_cmake_targets_not_defined}")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_cmake_targets_defined_text}\nTargets not yet defined: ${_cmake_targets_not_defined_text}\n")
endif()
unset(_cmake_targets_defined)
unset(_cmake_targets_not_defined)
unset(_cmake_expected_targets)


# Compute the installation prefix relative to this file.
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
if(_IMPORT_PREFIX STREQUAL "/")
  set(_IMPORT_PREFIX "")
endif()

# Create imported target Qt6::Gui
add_library(Qt6::Gui STATIC IMPORTED)

set_target_properties(Qt6::Gui PROPERTIES
  COMPATIBLE_INTERFACE_STRING "QT_MAJOR_VERSION"
  INTERFACE_COMPILE_DEFINITIONS "QT_GUI_LIB"
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include/QtGui;${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "Qt6::Core;\$<LINK_ONLY:Qt6::CorePrivate>;\$<LINK_ONLY:Qt6::PlatformModuleInternal>;\$<\$<AND:\$<NOT:\$<STREQUAL:\$<TARGET_PROPERTY:TYPE>,STATIC_LIBRARY>>,\$<NOT:\$<BOOL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_link_order_matters>>>,\$<NOT:\$<BOOL:\$<TARGET_PROPERTY:_qt_object_libraries_finalizer_mode>>>,\$<BOOL:TRUE>>:\$<TARGET_OBJECTS:Qt6::Gui_resources_1>>;Qt6::Gui_resources_1;\$<\$<AND:\$<NOT:\$<STREQUAL:\$<TARGET_PROPERTY:TYPE>,STATIC_LIBRARY>>,\$<NOT:\$<BOOL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_link_order_matters>>>,\$<NOT:\$<BOOL:\$<TARGET_PROPERTY:_qt_object_libraries_finalizer_mode>>>,\$<BOOL:TRUE>>:\$<TARGET_OBJECTS:Qt6::Gui_resources_2>>;Qt6::Gui_resources_2;d3d11;dxgi;dxguid;d3d12;\$<LINK_ONLY:advapi32>;\$<LINK_ONLY:gdi32>;\$<LINK_ONLY:ole32>;\$<LINK_ONLY:shell32>;\$<LINK_ONLY:user32>;\$<LINK_ONLY:WrapPNG::WrapPNG>;\$<LINK_ONLY:WrapHarfbuzz::WrapHarfbuzz>;\$<LINK_ONLY:WrapFreetype::WrapFreetype>;\$<LINK_ONLY:WrapFreetype::WrapFreetype>;\$<LINK_ONLY:d2d1>;\$<LINK_ONLY:dwrite>;\$<LINK_ONLY:Qt6::Core>"
  INTERFACE_LINK_OPTIONS "\$<\$<AND:\$<NOT:\$<STREQUAL:\$<TARGET_PROPERTY:TYPE>,STATIC_LIBRARY>>,\$<BOOL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_link_order_matters>>,\$<BOOL:\$<GENEX_EVAL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_cmp0099_policy_check>>>,\$<BOOL:TRUE>>:\$<TARGET_OBJECTS:Qt6::Gui_resources_1>>;\$<\$<AND:\$<NOT:\$<STREQUAL:\$<TARGET_PROPERTY:TYPE>,STATIC_LIBRARY>>,\$<BOOL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_link_order_matters>>,\$<BOOL:\$<GENEX_EVAL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_cmp0099_policy_check>>>,\$<BOOL:TRUE>>:\$<TARGET_OBJECTS:Qt6::Gui_resources_2>>"
  INTERFACE_QT_MAJOR_VERSION "6"
  INTERFACE_SOURCES "\$<\$<BOOL:\$<TARGET_PROPERTY:QT_CONSUMES_METATYPES>>:${_IMPORT_PREFIX}/./metatypes/qt6gui_release_metatypes.json>;\$<\$<AND:\$<NOT:\$<STREQUAL:\$<TARGET_PROPERTY:TYPE>,STATIC_LIBRARY>>,\$<BOOL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_link_order_matters>>,\$<NOT:\$<BOOL:\$<GENEX_EVAL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_cmp0099_policy_check>>>>,\$<NOT:\$<BOOL:\$<TARGET_PROPERTY:_qt_object_libraries_finalizer_mode>>>,\$<BOOL:TRUE>>:\$<TARGET_OBJECTS:Qt6::Gui_resources_1>>;\$<\$<AND:\$<NOT:\$<STREQUAL:\$<TARGET_PROPERTY:TYPE>,STATIC_LIBRARY>>,\$<BOOL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_link_order_matters>>,\$<NOT:\$<BOOL:\$<GENEX_EVAL:\$<TARGET_PROPERTY:Qt6::Platform,_qt_cmp0099_policy_check>>>>,\$<NOT:\$<BOOL:\$<TARGET_PROPERTY:_qt_object_libraries_finalizer_mode>>>,\$<BOOL:TRUE>>:\$<TARGET_OBJECTS:Qt6::Gui_resources_2>>"
  MODULE_PLUGIN_TYPES "accessiblebridge;platforms;platforms_darwin;xcbglintegrations;platformthemes;platforminputcontexts;generic;iconengines;imageformats;egldeviceintegrations"
  QT_DISABLED_PRIVATE_FEATURES "accessibility_atspi_bridge;directfb;evdev;system_freetype;fontconfig;system_harfbuzz;qqnx_imf;integrityfb;kms;drm_atomic;libinput;integrityhid;libinput_axis_api;libinput_hires_wheel_support;linuxfb;vsp2;vnc;mtdev;vkkhrdisplay;egl_x11;eglfs;eglfs_brcm;eglfs_egldevice;eglfs_gbm;eglfs_vsp2;eglfs_mali;eglfs_viv;eglfs_rcar;eglfs_viv_wl;eglfs_openwfd;eglfs_x11;system_jpeg;system_png;tslib;xcb_glx;xcb_egl_plugin;xcb_native_painting;xrender;xcb_xlib;xcb_sm;system_xcb_xinput;xkbcommon;xkbcommon_x11;xlib"
  QT_DISABLED_PUBLIC_FEATURES "accessibility_atspi_bridge;fontconfig;opengles2;opengles3;opengles31;opengles32;vulkan;openvg;egl;xcb;xcb_glx_plugin;system_textmarkdownreader"
  QT_ENABLED_PRIVATE_FEATURES "directwrite;directwrite3;direct2d;direct2d1_1;freetype;harfbuzz;vkgen;gif;ico;jpeg;png;imageio_text_loading;tuiotouch;multiprocess;raster_64bit;raster_fp"
  QT_ENABLED_PUBLIC_FEATURES "freetype;harfbuzz;dynamicgl;opengl;ico;sessionmanager;texthtmlparser;textmarkdownreader;textmarkdownwriter;textodfwriter;cssparser;draganddrop;action;cursor;clipboard;wheelevent;tabletevent;im;highdpiscaling;validator;standarditemmodel;filesystemmodel;imageformatplugin;movie;imageformat_bmp;imageformat_ppm;imageformat_xbm;imageformat_xpm;imageformat_png;imageformat_jpeg;image_heuristic_mask;image_text;picture;colornames;pdf;desktopservices;systemtrayicon;accessibility;whatsthis;undocommand;undostack;undogroup"
  QT_QMAKE_PRIVATE_CONFIG ""
  QT_QMAKE_PUBLIC_CONFIG ""
  QT_QMAKE_PUBLIC_QT_CONFIG ""
  _qt_config_module_name "gui"
  _qt_is_public_module "TRUE"
  _qt_module_has_headers "ON"
  _qt_module_has_private_headers "TRUE"
  _qt_module_has_public_headers "TRUE"
  _qt_module_has_qpa_headers "TRUE"
  _qt_module_has_rhi_headers "TRUE"
  _qt_module_include_name "QtGui"
  _qt_module_interface_name "Gui"
  _qt_package_name "Qt6Gui"
  _qt_package_version "6.6.0"
  _qt_private_module_target_name "GuiPrivate"
)

# Create imported target Qt6::GuiPrivate
add_library(Qt6::GuiPrivate INTERFACE IMPORTED)

set_target_properties(Qt6::GuiPrivate PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "\$<\$<BOOL:\$<TARGET_PROPERTY:Qt6::Gui,_qt_module_has_private_headers>>:>;\$<\$<BOOL:\$<TARGET_PROPERTY:Qt6::Gui,_qt_module_has_private_headers>>:>;\$<\$<BOOL:\$<TARGET_PROPERTY:Qt6::Gui,_qt_module_has_private_headers>>:${_IMPORT_PREFIX}/include/QtGui/6.6.0>;\$<\$<BOOL:\$<TARGET_PROPERTY:Qt6::Gui,_qt_module_has_private_headers>>:${_IMPORT_PREFIX}/include/QtGui/6.6.0/QtGui>"
  INTERFACE_LINK_LIBRARIES "Qt6::CorePrivate;Qt6::Gui"
  _qt_config_module_name "gui_private"
  _qt_is_private_module "TRUE"
  _qt_package_name "Qt6Gui"
  _qt_package_version "6.6.0"
  _qt_public_module_target_name "Gui"
)

# Create imported target Qt6::Gui_resources_1
add_library(Qt6::Gui_resources_1 OBJECT IMPORTED)

set_target_properties(Qt6::Gui_resources_1 PROPERTIES
  INTERFACE_LINK_LIBRARIES "Qt6::Core;\$<LINK_ONLY:Qt6::Platform>;\$<LINK_ONLY:Qt6::PlatformModuleInternal>"
  _is_qt_propagated_object_library "TRUE"
)

# Create imported target Qt6::Gui_resources_2
add_library(Qt6::Gui_resources_2 OBJECT IMPORTED)

set_target_properties(Qt6::Gui_resources_2 PROPERTIES
  INTERFACE_LINK_LIBRARIES "Qt6::Core;\$<LINK_ONLY:Qt6::Platform>;\$<LINK_ONLY:Qt6::PlatformModuleInternal>"
  _is_qt_propagated_object_library "TRUE"
)

if(CMAKE_VERSION VERSION_LESS 3.1.0)
  message(FATAL_ERROR "This file relies on consumers using CMake 3.1.0 or greater.")
endif()

# Load information for each installed configuration.
file(GLOB _cmake_config_files "${CMAKE_CURRENT_LIST_DIR}/Qt6GuiTargets-*.cmake")
foreach(_cmake_config_file IN LISTS _cmake_config_files)
  include("${_cmake_config_file}")
endforeach()
unset(_cmake_config_file)
unset(_cmake_config_files)

# Cleanup temporary variables.
set(_IMPORT_PREFIX)

# Loop over all imported files and verify that they actually exist
foreach(_cmake_target IN LISTS _cmake_import_check_targets)
  foreach(_cmake_file IN LISTS "_cmake_import_check_files_for_${_cmake_target}")
    if(NOT EXISTS "${_cmake_file}")
      message(FATAL_ERROR "The imported target \"${_cmake_target}\" references the file
   \"${_cmake_file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
  endforeach()
  unset(_cmake_file)
  unset("_cmake_import_check_files_for_${_cmake_target}")
endforeach()
unset(_cmake_target)
unset(_cmake_import_check_targets)

# Make sure the targets which have been exported in some other
# export set exist.
unset(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets)
foreach(_target "Qt6::Platform" "Qt6::Core" "Qt6::CorePrivate" "Qt6::PlatformModuleInternal" )
  if(NOT TARGET "${_target}" )
    set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets "${${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets} ${_target}")
  endif()
endforeach()

if(DEFINED ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets)
  if(CMAKE_FIND_PACKAGE_NAME)
    set( ${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
    set( ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE "The following imported targets are referenced, but are missing: ${${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets}")
  else()
    message(FATAL_ERROR "The following imported targets are referenced, but are missing: ${${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets}")
  endif()
endif()
unset(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets)

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
