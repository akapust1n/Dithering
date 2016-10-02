#-------------------------------------------------
#
# Project created by QtCreator 2016-07-12T01:00:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_dithering_pixmap
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Dithering.cpp \
    MainManager.cpp \
    DitherManager.cpp \
    DataManager.cpp

HEADERS  += MainWindow.h \
    Dithering.h \
    MainManager.h \
    Quality.h \
    DitherManager.h \
    DataManager.h

FORMS    += MainWindow.ui
CONFIG += c++14
