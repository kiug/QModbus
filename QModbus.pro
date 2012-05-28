QT -= gui

CONFIG += libmodbus

#TARGET = QModbus
TEMPLATE = lib

DEFINES += QMODBUS_LIBRARY

SOURCES += qmodbus.cpp \
    qmodbusbits.cpp \
    qmodbusregisters.cpp

HEADERS += qmodbus.h\
    qmodbusbits.h \
    qmodbusregisters.h

CONFIG(debug, debug|release) {
    TARGET = QModbusd
}
else {
    TARGET = QModbus
}
