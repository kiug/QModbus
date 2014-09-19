QT       += core gui

TARGET = modbus_master
TEMPLATE = app

CONFIG += QModbus

DESTDIR = ../QModbus-build-desktop/release

#LIBS += -L"../../QModbus-build-desktop/release"
#LIBS += -lQModbus3

SOURCES +=\
        mainwindow.cpp \
    qmodbusmastergui.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
