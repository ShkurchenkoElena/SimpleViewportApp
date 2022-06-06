!VIEWPORT_PRI {

CONFIG += VIEWPORT_PRI

INCLUDEPATH += $$PWD

include($$PWD/../Camera/Camera.pri)

HEADERS += \
    $$PWD/viewport.h

SOURCES += \
    $$PWD/viewport.cpp

}

HEADERS += \
    $$PWD/navigation.h

SOURCES += \
    $$PWD/navigation.cpp
