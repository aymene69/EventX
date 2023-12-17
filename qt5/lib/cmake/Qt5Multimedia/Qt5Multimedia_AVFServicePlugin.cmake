
add_library(Qt5::AVFServicePlugin MODULE IMPORTED)


_populate_Multimedia_plugin_properties(AVFServicePlugin RELEASE "mediaservice/libqavfcamera.dylib" FALSE)

list(APPEND Qt5Multimedia_PLUGINS Qt5::AVFServicePlugin)
set_property(TARGET Qt5::Multimedia APPEND PROPERTY QT_ALL_PLUGINS_mediaservice Qt5::AVFServicePlugin)
set_property(TARGET Qt5::AVFServicePlugin PROPERTY QT_PLUGIN_TYPE "mediaservice")
set_property(TARGET Qt5::AVFServicePlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::AVFServicePlugin PROPERTY QT_PLUGIN_CLASS_NAME "AVFServicePlugin")
