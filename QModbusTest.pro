# http://taat.pl/artykuly/git-po-polsku/

TEMPLATE = app
QT -= gui

CONFIG += console
CONFIG -= app_bundle
CONFIG  += qtestlib
CONFIG += libmodbus

DESTDIR = ../QModbus-build-desktop/debug

LIBS += -L"../QModbus-build-desktop/debug"
LIBS += -lQModbusd3

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