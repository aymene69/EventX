
add_library(Qt5::CoreAudioPlugin MODULE IMPORTED)


_populate_Multimedia_plugin_properties(CoreAudioPlugin RELEASE "audio/libqtaudio_coreaudio.dylib" FALSE)

list(APPEND Qt5Multimedia_PLUGINS Qt5::CoreAudioPlugin)
set_property(TARGET Qt5::Multimedia APPEND PROPERTY QT_ALL_PLUGINS_audio Qt5::CoreAudioPlugin)
set_property(TARGET Qt5::CoreAudioPlugin PROPERTY QT_PLUGIN_TYPE "audio")
set_property(TARGET Qt5::CoreAudioPlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::CoreAudioPlugin PROPERTY QT_PLUGIN_CLASS_NAME "CoreAudioPlugin")
