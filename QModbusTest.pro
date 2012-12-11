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

SOURCES += main.cpp \
    testqmodbusbits.cpp \
    testqmodbusregisters.cpp \
    testqmodbusslave.cpp \
    testqmodbuserror.cpp \
    testqmodbusmaster.cpp

HEADERS += \
    testqmodbusbits.h \
    testqmodbusregisters.h \
    testqmodbusslave.h \
    testqmodbuserror.h \
    testqmodbusmaster.h
