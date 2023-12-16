
add_library(Qt5::QMacHeifPlugin MODULE IMPORTED)


_populate_Gui_plugin_properties(QMacHeifPlugin RELEASE "imageformats/libqmacheif.dylib" FALSE)

list(APPEND Qt5Gui_PLUGINS Qt5::QMacHeifPlugin)
set_property(TARGET Qt5::Gui APPEND PROPERTY QT_ALL_PLUGINS_imageformats Qt5::QMacHeifPlugin)
set_property(TARGET Qt5::QMacHeifPlugin PROPERTY QT_PLUGIN_TYPE "imageformats")
set_property(TARGET Qt5::QMacHeifPlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::QMacHeifPlugin PROPERTY QT_PLUGIN_CLASS_NAME "QMacHeifPlugin")
