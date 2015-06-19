#-------------------------------------------------
#
# Project created by QtCreator 2015-06-12T22:36:20
#
#-------------------------------------------------
QT       += core

QT       -= gui

TARGET = fixpointclass
CONFIG   += console

CONFIG += C++11

TEMPLATE = app

SOURCES += main.cpp \
    fixpoint.cpp

HEADERS += \
    fixpoint.hpp
QMAKE_CXXFLAGS += -std=c++11
