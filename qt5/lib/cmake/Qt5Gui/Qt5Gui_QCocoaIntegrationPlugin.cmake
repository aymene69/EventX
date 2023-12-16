
add_library(Qt5::QCocoaIntegrationPlugin MODULE IMPORTED)


_populate_Gui_plugin_properties(QCocoaIntegrationPlugin RELEASE "platforms/libqcocoa.dylib" FALSE)

list(APPEND Qt5Gui_PLUGINS Qt5::QCocoaIntegrationPlugin)
set_property(TARGET Qt5::Gui APPEND PROPERTY QT_ALL_PLUGINS_platforms Qt5::QCocoaIntegrationPlugin)
set_property(TARGET Qt5::QCocoaIntegrationPlugin PROPERTY QT_PLUGIN_TYPE "platforms")
set_property(TARGET Qt5::QCocoaIntegrationPlugin PROPERTY QT_PLUGIN_EXTENDS "-")
set_property(TARGET Qt5::QCocoaIntegrationPlugin PROPERTY QT_PLUGIN_CLASS_NAME "QCocoaIntegrationPlugin")
