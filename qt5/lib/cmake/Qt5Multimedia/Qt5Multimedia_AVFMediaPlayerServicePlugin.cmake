
add_library(Qt5::AVFMediaPlayerServicePlugin MODULE IMPORTED)


_populate_Multimedia_plugin_properties(AVFMediaPlayerServicePlugin RELEASE "mediaservice/libqavfmediaplayer.dylib" FALSE)

list(APPEND Qt5Multimedia_PLUGINS Qt5::AVFMediaPlayerServicePlugin)
set_property(TARGET Qt5::Multimedia APPEND PROPERTY QT_ALL_PLUGINS_mediaservice Qt5::AVFMediaPlayerServicePlugin)
set_property(TARGET Qt5::AVFMediaPlayerServicePlugin PROPERTY QT_PLUGIN_TYPE "mediaservice")
set_property(TARGET Qt5::AVFMediaPlayerServicePlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::AVFMediaPlayerServicePlugin PROPERTY QT_PLUGIN_CLASS_NAME "AVFMediaPlayerServicePlugin")
