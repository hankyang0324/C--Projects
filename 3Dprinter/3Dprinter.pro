TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    curves.cpp \
    path.cpp \
    twod.cpp \
    threed.cpp

HEADERS += \
    curves.h \
    path.h \
    twod.h \
    threed.h
