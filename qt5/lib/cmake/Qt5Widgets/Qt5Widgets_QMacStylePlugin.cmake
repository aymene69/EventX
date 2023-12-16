
add_library(Qt5::QMacStylePlugin MODULE IMPORTED)


_populate_Widgets_plugin_properties(QMacStylePlugin RELEASE "styles/libqmacstyle.dylib" FALSE)

list(APPEND Qt5Widgets_PLUGINS Qt5::QMacStylePlugin)
set_property(TARGET Qt5::Widgets APPEND PROPERTY QT_ALL_PLUGINS_styles Qt5::QMacStylePlugin)
set_property(TARGET Qt5::QMacStylePlugin PROPERTY QT_PLUGIN_TYPE "styles")
set_property(TARGET Qt5::QMacStylePlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::QMacStylePlugin PROPERTY QT_PLUGIN_CLASS_NAME "QMacStylePlugin")
