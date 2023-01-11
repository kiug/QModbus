QT -= gui

CONFIG += libmodbus-3.1.10

TEMPLATE = lib

DEFINES += QMODBUS_LIBRARY

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

DISTFILES += \
    QModbus.prf \
    libmodbus-3.1.10.prf
