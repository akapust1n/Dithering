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
    DataRead.cpp \
    Dithering.cpp

HEADERS  += MainWindow.h \
    DataRead.h \
    Dithering.h

FORMS    += MainWindow.ui
