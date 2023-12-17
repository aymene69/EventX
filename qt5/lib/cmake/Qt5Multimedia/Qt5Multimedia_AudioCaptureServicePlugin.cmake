
add_library(Qt5::AudioCaptureServicePlugin MODULE IMPORTED)


_populate_Multimedia_plugin_properties(AudioCaptureServicePlugin RELEASE "mediaservice/libqtmedia_audioengine.dylib" FALSE)

list(APPEND Qt5Multimedia_PLUGINS Qt5::AudioCaptureServicePlugin)
set_property(TARGET Qt5::Multimedia APPEND PROPERTY QT_ALL_PLUGINS_mediaservice Qt5::AudioCaptureServicePlugin)
set_property(TARGET Qt5::AudioCaptureServicePlugin PROPERTY QT_PLUGIN_TYPE "mediaservice")
set_property(TARGET Qt5::AudioCaptureServicePlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::AudioCaptureServicePlugin PROPERTY QT_PLUGIN_CLASS_NAME "AudioCaptureServicePlugin")
