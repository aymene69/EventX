
add_library(Qt5::QCocoaPrinterSupportPlugin MODULE IMPORTED)


_populate_PrintSupport_plugin_properties(QCocoaPrinterSupportPlugin RELEASE "printsupport/libcocoaprintersupport.dylib" FALSE)

list(APPEND Qt5PrintSupport_PLUGINS Qt5::QCocoaPrinterSupportPlugin)
set_property(TARGET Qt5::PrintSupport APPEND PROPERTY QT_ALL_PLUGINS_printsupport Qt5::QCocoaPrinterSupportPlugin)
set_property(TARGET Qt5::QCocoaPrinterSupportPlugin PROPERTY QT_PLUGIN_TYPE "printsupport")
set_property(TARGET Qt5::QCocoaPrinterSupportPlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::QCocoaPrinterSupportPlugin PROPERTY QT_PLUGIN_CLASS_NAME "QCocoaPrinterSupportPlugin")
