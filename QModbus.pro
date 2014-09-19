# http://taat.pl/artykuly/git-po-polsku/

QT -= gui

CONFIG += libmodbus

#TARGET = QModbus
TEMPLATE = lib

DEFINES += QMODBUS_LIBRARY

SOURCES += \
    qmodbusbits.cpp \
    qmodbusregisters.cpp \
    qmodbuserror.cpp \
    qmodbusmaster.cpp

HEADERS +=\
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
