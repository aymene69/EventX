
add_library(Qt5::QTextToSpeechPluginOsx MODULE IMPORTED)


_populate_TextToSpeech_plugin_properties(QTextToSpeechPluginOsx RELEASE "texttospeech/libqtexttospeech_speechosx.dylib" FALSE)

list(APPEND Qt5TextToSpeech_PLUGINS Qt5::QTextToSpeechPluginOsx)
set_property(TARGET Qt5::TextToSpeech APPEND PROPERTY QT_ALL_PLUGINS_texttospeech Qt5::QTextToSpeechPluginOsx)
set_property(TARGET Qt5::QTextToSpeechPluginOsx PROPERTY QT_PLUGIN_TYPE "texttospeech")
set_property(TARGET Qt5::QTextToSpeechPluginOsx PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::QTextToSpeechPluginOsx PROPERTY QT_PLUGIN_CLASS_NAME "QTextToSpeechPluginOsx")
