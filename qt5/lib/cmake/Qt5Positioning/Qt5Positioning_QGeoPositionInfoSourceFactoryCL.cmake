
add_library(Qt5::QGeoPositionInfoSourceFactoryCL MODULE IMPORTED)


_populate_Positioning_plugin_properties(QGeoPositionInfoSourceFactoryCL RELEASE "position/libqtposition_cl.dylib" FALSE)

list(APPEND Qt5Positioning_PLUGINS Qt5::QGeoPositionInfoSourceFactoryCL)
set_property(TARGET Qt5::Positioning APPEND PROPERTY QT_ALL_PLUGINS_position Qt5::QGeoPositionInfoSourceFactoryCL)
set_property(TARGET Qt5::QGeoPositionInfoSourceFactoryCL PROPERTY QT_PLUGIN_TYPE "position")
set_property(TARGET Qt5::QGeoPositionInfoSourceFactoryCL PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::QGeoPositionInfoSourceFactoryCL PROPERTY QT_PLUGIN_CLASS_NAME "QGeoPositionInfoSourceFactoryCL")
