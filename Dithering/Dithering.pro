#-------------------------------------------------
#
# Project created by QtCreator 2016-11-26T16:40:46
#
#-------------------------------------------------

QT += core gui widgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

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
    YlioumaDith.cpp \
    OGLWidget.cpp

HEADERS  += MainWindow.h \
    DataManager.h \
    MainManager.h \
    DitherManager.h \
    Dithering.h \
    ColorMap.h \
    MetricsManager.h \
    Metrics.h \
    YlioumaDith.h \
    OGLWidget.h

FORMS    += MainWindow.ui
CONFIG += c++14
CONFIG += o4
QMAKE_CXXFLAGS += -std=c++1z
QMAKE_CXXFLAGS += $(shell Magick++-config --cppflags --cxxflags)
#LIBS += -lMagick++
LIBS +=$(shell Magick++-config --ldflags --libs)
#INCLUDEPATH += /usr/include/ImageMagick-6
