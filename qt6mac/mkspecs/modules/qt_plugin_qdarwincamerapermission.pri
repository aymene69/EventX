QT_PLUGIN.qdarwincamerapermission.TYPE = permissions
QT_PLUGIN.qdarwincamerapermission.EXTENDS = -
QT_PLUGIN.qdarwincamerapermission.DEPENDS = core
QT_PLUGIN.qdarwincamerapermission.CLASS_NAME = QDarwinCameraPermissionPlugin
QT_PLUGIN.qdarwincamerapermission.module_config = v2 staticlib
QT_PLUGINS += qdarwincamerapermission
QT_PLUGIN.qdarwincamerapermission.usage_descriptions = NSCameraUsageDescription
QT_PLUGIN.qdarwincamerapermission.request_flag = -Wl,-u,_QDarwinCameraPermissionRequest