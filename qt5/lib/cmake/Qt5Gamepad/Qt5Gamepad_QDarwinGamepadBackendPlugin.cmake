
add_library(Qt5::QDarwinGamepadBackendPlugin MODULE IMPORTED)


_populate_Gamepad_plugin_properties(QDarwinGamepadBackendPlugin RELEASE "gamepads/libdarwingamepad.dylib" FALSE)

list(APPEND Qt5Gamepad_PLUGINS Qt5::QDarwinGamepadBackendPlugin)
set_property(TARGET Qt5::Gamepad APPEND PROPERTY QT_ALL_PLUGINS_gamepads Qt5::QDarwinGamepadBackendPlugin)
set_property(TARGET Qt5::QDarwinGamepadBackendPlugin PROPERTY QT_PLUGIN_TYPE "gamepads")
set_property(TARGET Qt5::QDarwinGamepadBackendPlugin PROPERTY QT_PLUGIN_EXTENDS "Qt::Gamepad")
set_property(TARGET Qt5::QDarwinGamepadBackendPlugin PROPERTY QT_PLUGIN_CLASS_NAME "QDarwinGamepadBackendPlugin")
