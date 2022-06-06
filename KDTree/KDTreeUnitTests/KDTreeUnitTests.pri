!KDTREE_UNITTESTS_PRI {

CONFIG += KDTREE_UNITTESTS_PRI
INCLUDEPATH *= $$clean_path($$PWD/../)

include($$PWD/../KDTree/KDTree.pri)

HEADERS += \
    $$PWD/kdtreetests.h \
    $$PWD/utilstests.h

SOURCES += \
    $$PWD/kdtreetests.cpp \
    $$PWD/utilstests.cpp

}    
