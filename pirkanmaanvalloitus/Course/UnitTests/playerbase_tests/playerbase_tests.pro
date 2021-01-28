QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    $$PWD/../../CourseLib/core/gameobject.h \
    $$PWD/../../CourseLib/core/coordinate.h \
    $$PWD/../../CourseLib/core/playerbase.h

SOURCES +=  \
    $$PWD/../../CourseLib/core/playerbase.cpp \
    $$PWD/../../CourseLib/core/gameobject.cpp \
    $$PWD/../../CourseLib/core/coordinate.cpp \
    tst_default_playerbase.cpp

INCLUDEPATH += \
    $$PWD/../../CourseLib/
