QT += testlib
QT += gui

CONFIG += qt console warn_on depend_includepath testcase


TEMPLATE = app

INCLUDEPATH += ../../Game/
DEPENDPATH += ../../Game/

SOURCES +=  tst_gameeventhandlertest.cpp \

