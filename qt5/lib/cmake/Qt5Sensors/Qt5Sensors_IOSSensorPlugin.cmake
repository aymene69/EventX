
add_library(Qt5::IOSSensorPlugin MODULE IMPORTED)


_populate_Sensors_plugin_properties(IOSSensorPlugin RELEASE "sensors/libqtsensors_ios.dylib" FALSE)

list(APPEND Qt5Sensors_PLUGINS Qt5::IOSSensorPlugin)
set_property(TARGET Qt5::Sensors APPEND PROPERTY QT_ALL_PLUGINS_sensors Qt5::IOSSensorPlugin)
set_property(TARGET Qt5::IOSSensorPlugin PROPERTY QT_PLUGIN_TYPE "sensors")
set_property(TARGET Qt5::IOSSensorPlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::IOSSensorPlugin PROPERTY QT_PLUGIN_CLASS_NAME "IOSSensorPlugin")
