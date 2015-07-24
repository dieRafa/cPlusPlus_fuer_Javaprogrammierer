TEMPLATE = app
CONFIG += console
CONFIG +=  C++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fix_point_oo.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    fix_point_oo.hpp

