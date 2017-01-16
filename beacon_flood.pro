TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    mybeacon.cpp
LIBS += -ltins

HEADERS += \
    mybeacon.h
