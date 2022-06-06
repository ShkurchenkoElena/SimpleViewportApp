QT += core gui testlib

CONFIG += c++17
CONFIG += object_parallel_to_source
DEFINES += QT_DEPRECATED_WARNINGS

include($$PWD/../KDTreeUnitTests/KDTreeUnitTests.pri)

SOURCES += main.cpp
