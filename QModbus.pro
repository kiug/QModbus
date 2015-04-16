QT -= gui

CONFIG += libmodbus

TEMPLATE = lib

DEFINES += QMODBUS_LIBRARY
#-Ilibmodbus

DESTDIR = ../QModbus_BIN

SOURCES += \
    qmodbusbits.cpp \
    qmodbusregisters.cpp \
    qmodbuserror.cpp \
    qmodbusmaster.cpp

HEADERS += \
    qmodbusbits.h \
    qmodbusregisters.h \
    qmodbuserror.h \
    qmodbusmaster.h \
    qmodbus.h

CONFIG(debug, debug|release) {
    TARGET = QModbusd
}
else {
    TARGET = QModbus
}
