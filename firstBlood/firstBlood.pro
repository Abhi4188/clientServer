#-------------------------------------------------
#
# Project created by QtCreator 2017-07-19T18:41:45
#
#-------------------------------------------------

QT       += core gui webkit network
QT       += webkitwidgets

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = firstBlood
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form1.cpp

HEADERS  += mainwindow.h \
    form1.h

FORMS    += mainwindow.ui \
    form1.ui
