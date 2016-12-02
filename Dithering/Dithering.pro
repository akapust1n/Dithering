#-------------------------------------------------
#
# Project created by QtCreator 2016-11-26T16:40:46
#
#-------------------------------------------------

QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dithering
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    DataManager.cpp \
    MainManager.cpp \
    DitherManager.cpp \
    Dithering.cpp \
    ColorMap.cpp \
    MetricsManager.cpp \
    Metrics.cpp \
    ImageViewer.cpp

HEADERS  += MainWindow.h \
    DataManager.h \
    MainManager.h \
    DitherManager.h \
    Dithering.h \
    ColorMap.h \
    MetricsManager.h \
    Metrics.h \
    ImageViewer.h

FORMS    += MainWindow.ui
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++1z
QMAKE_CXXFLAGS += $(shell Magick++-config --cppflags --cxxflags)
#LIBS += -lMagick++
LIBS +=$(shell Magick++-config --ldflags --libs)
#INCLUDEPATH += /usr/include/ImageMagick-6
