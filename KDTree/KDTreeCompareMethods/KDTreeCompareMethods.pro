QT += core gui testlib

CONFIG += c++17
CONFIG += object_parallel_to_source
DEFINES += QT_DEPRECATED_WARNINGS

include($$PWD/../KDTree/KDTree.pri)
include($$PWD/../KDTreeUnitTests/KDTreeUnitTests.pri)

SOURCES += main.cpp \
    timetester.cpp

HEADERS += \
    timetester.h
