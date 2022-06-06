!KDTREE_PRI {

CONFIG += KDTREE_PRI
INCLUDEPATH *= $$clean_path($$PWD/../)

HEADERS += \
    $$PWD/kdtree.h \
    $$PWD/node.h \
    $$PWD/nodeinner.h \
    $$PWD/nodeleaf.h \
    $$PWD/utils.h

SOURCES += \
    $$PWD/kdtree.cpp \
    $$PWD/node.cpp \
    $$PWD/nodeinner.cpp \
    $$PWD/nodeleaf.cpp \
    $$PWD/utils.cpp
}
