QT += core network
QT -= gui

TARGET = server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mainServer.cpp

HEADERS += \
    mainServer.h

