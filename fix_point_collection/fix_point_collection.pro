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

SOURCES += \
    fixpoint_oo.cpp \
    fix_point_collection.cpp \
    test_fix_point_collection.cpp

HEADERS += \
    fixpoint_oo.hpp \
    fix_point_collection.hpp

QMAKE_CXXFLAGS += -std=c++11
