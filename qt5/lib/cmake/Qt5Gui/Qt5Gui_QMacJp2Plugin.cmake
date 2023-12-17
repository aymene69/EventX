
add_library(Qt5::QMacJp2Plugin MODULE IMPORTED)


_populate_Gui_plugin_properties(QMacJp2Plugin RELEASE "imageformats/libqmacjp2.dylib" FALSE)

list(APPEND Qt5Gui_PLUGINS Qt5::QMacJp2Plugin)
set_property(TARGET Qt5::Gui APPEND PROPERTY QT_ALL_PLUGINS_imageformats Qt5::QMacJp2Plugin)
set_property(TARGET Qt5::QMacJp2Plugin PROPERTY QT_PLUGIN_TYPE "imageformats")
set_property(TARGET Qt5::QMacJp2Plugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::QMacJp2Plugin PROPERTY QT_PLUGIN_CLASS_NAME "QMacJp2Plugin")
