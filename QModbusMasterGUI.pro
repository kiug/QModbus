QT += core gui widgets

TARGET = modbus_master
TEMPLATE = app

CONFIG += QModbus

DESTDIR = ../QModbus_BIN

SOURCES += \
    mainwindow.cpp \
    qmodbusmastergui.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui
