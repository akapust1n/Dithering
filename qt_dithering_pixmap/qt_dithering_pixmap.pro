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
    DataManager.cpp \
    Metrics.cpp \
    PSNR.cpp \
    SSIM.cpp \
    Method.cpp \
    ColorMap.cpp

HEADERS  += MainWindow.h \
    Dithering.h \
    MainManager.h \
    DitherManager.h \
    DataManager.h \
    Metrics.h \
    PSNR.h \
    SSIM.h \
    Method.h \
    ColorMap.h

FORMS    += MainWindow.ui
CONFIG += c++14

QMAKE_CXXFLAGS += $(shell Magick++-config --cppflags --cxxflags)
LIBS += -lMagick++


