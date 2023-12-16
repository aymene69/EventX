QT.bluetooth.VERSION = 5.15.2
QT.bluetooth.name = QtBluetooth
QT.bluetooth.module = QtBluetooth
QT.bluetooth.libs = $$QT_MODULE_LIB_BASE
QT.bluetooth.includes = $$QT_MODULE_LIB_BASE/QtBluetooth.framework/Headers
QT.bluetooth.frameworks = $$QT_MODULE_LIB_BASE
QT.bluetooth.bins = $$QT_MODULE_BIN_BASE
QT.bluetooth.depends = core
QT.bluetooth.run_depends = concurrent
QT.bluetooth.uses =
QT.bluetooth.module_config = v2 lib_bundle
QT.bluetooth.DEFINES = QT_BLUETOOTH_LIB
QT.bluetooth.enabled_features =
QT.bluetooth.disabled_features = bluez native-win32-bluetooth
QT_CONFIG +=
QT_MODULES += bluetooth
