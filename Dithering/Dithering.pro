#-------------------------------------------------
#
# Project created by QtCreator 2016-11-26T16:40:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dithering
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    DataManager.cpp \
    MainManager.cpp

HEADERS  += MainWindow.h \
    DataManager.h \
    MainManager.h

FORMS    += MainWindow.ui
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++1z
