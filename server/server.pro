QT += core network
QT -= gui

TARGET = server
CONFIG += console c++14
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mainServer.cpp

HEADERS += \
    mainServer.h

