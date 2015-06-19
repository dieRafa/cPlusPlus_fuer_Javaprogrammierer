TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

QMAKE_CXXFLAGS += -Winline

SOURCES += main.cpp \
    fix_point.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    fix_point.h

