QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = graphics-example

HEADERS = \
    simpleitem.h

SOURCES = \
    main.cpp



unix|win32: LIBS += -L$$PWD/../graphics_library/source/lib/ -lgraphics

INCLUDEPATH += $$PWD/../graphics_library/source/include
DEPENDPATH += $$PWD/../graphics_library/source/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../graphics_library/source/lib/graphics.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../graphics_library/source/lib/libgraphics.a
