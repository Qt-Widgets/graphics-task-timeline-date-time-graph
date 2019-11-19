QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
TARGET = graphics

CODECFORSRC = UTF-8

DESTDIR = $$PWD/source/lib
DLLDESTDIR = DESTDIR

DEFINES += GRAPHICS_LIBRARY

INCLUDEPATH += \
    source

HEADERS += \
    source/include/abstractplotitem.h \
    source/include/abstractplotlayout.h \
    source/include/abstractplotscene.h \
    source/include/abstractplotview.h \
    source/include/abstractscaleengine.h \
    source/include/abstractscale.h \
    source/include/commonprerequisites.h \
    source/include/datetimescaleengine.h \
    source/include/datetimescale.h \
    source/include/datetimescaleplotitem.h \
    source/include/infiniteplotscene.h \
    source/include/interactiveplotitem.h \
    source/include/numericscale.h \
    source/include/sectionscale.h \
    source/include/standardplotitem.h \
    source/include/standardplotlayout.h \
    source/include/standardplotscene.h \
    source/include/standardplotview.h \
    source/include/converter.h

SOURCES += \
    source/abstractplotitem.cpp \
    source/abstractplotscene.cpp \
    source/abstractplotview.cpp \
    source/datetimescale.cpp \
    source/datetimescaleengine.cpp \
    source/datetimescaleplotitem.cpp \
    source/infiniteplotscene.cpp \
    source/interactiveplotitem.cpp \
    source/numericscale.cpp \
    source/sectionscale.cpp \
    source/standardplotitem.cpp \
    source/standardplotlayout.cpp \
    source/standardplotscene.cpp \
    source/standardplotview.cpp \
    source/converter.cpp
