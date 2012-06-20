# http://taat.pl/artykuly/git-po-polsku/

QT -= gui

CONFIG += libmodbus

#TARGET = QModbus
TEMPLATE = lib

DEFINES += QMODBUS_LIBRARY

SOURCES += qmodbus.cpp \
    qmodbusbits.cpp \
    qmodbusregisters.cpp \
    qmodbuserror.cpp

HEADERS += qmodbus.h\
    qmodbusbits.h \
    qmodbusregisters.h \
    qmodbuserror.h

CONFIG(debug, debug|release) {
    TARGET = QModbusd
}
else {
    TARGET = QModbus
}
