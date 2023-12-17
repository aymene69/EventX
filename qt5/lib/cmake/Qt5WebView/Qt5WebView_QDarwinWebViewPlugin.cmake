
add_library(Qt5::QDarwinWebViewPlugin MODULE IMPORTED)


_populate_WebView_plugin_properties(QDarwinWebViewPlugin RELEASE "webview/libqtwebview_darwin.dylib" FALSE)

list(APPEND Qt5WebView_PLUGINS Qt5::QDarwinWebViewPlugin)
set_property(TARGET Qt5::WebView APPEND PROPERTY QT_ALL_PLUGINS_webview Qt5::QDarwinWebViewPlugin)
set_property(TARGET Qt5::QDarwinWebViewPlugin PROPERTY QT_PLUGIN_TYPE "webview")
set_property(TARGET Qt5::QDarwinWebViewPlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::QDarwinWebViewPlugin PROPERTY QT_PLUGIN_CLASS_NAME "QDarwinWebViewPlugin")
