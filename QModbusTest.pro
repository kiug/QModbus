QT += widgets testlib

CONFIG += libmodbus

LIBS += -L"../QModbus_BIN"
LIBS += -lQModbus3

SOURCES += \
    testqmodbusbits.cpp \
    testqmodbusregisters.cpp \
    testqmodbuserror.cpp \
    testqmodbusmaster.cpp \
    qmodbustest.cpp

HEADERS += \
    testqmodbusbits.h \
    testqmodbusregisters.h \
    testqmodbuserror.h \
    testqmodbusmaster.h
