#-------------------------------------------------
#
# Project created by QtCreator 2019-10-23T14:59:31
#
#-------------------------------------------------

QT       += core gui widgets
QT += gui

CONFIG += c++14

TARGET = TheGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    buildings/farm.cpp \
    buildings/house.cpp \
    handlers/buildinghandler.cpp \
    main.cpp \
    mainwindow.cpp \
    settingwindow.cpp \
    graphics/mapitem.cpp \
    graphics/gamescene.cpp \
    graphics/map.cpp \
    handlers/gameeventhandler.cpp \
    handlers/objectmanager.cpp \
    tiles/stone.cpp \
    tiles/water.cpp \
    buildings/bridge.cpp \
    tiles/sand.cpp \
    buildings/market.cpp \
    winwindow.cpp \
    losewindow.cpp




HEADERS += \
    buildings/farm.h \
    buildings/house.h \
    handlers/buildinghandler.h \
    mainwindow.hh \
    resources.h \
    settingwindow.hh \
    graphics/mapitem.h \
    graphics/gamescene.h \
    graphics/map.h \
    graphics/mapitem.h \
    handlers/gameeventhandler.h \
    handlers/objectmanager.h \
    tiles/stone.h \
    tiles/water.h \
    buildings/bridge.h \
    tiles/sand.h \
    buildings/market.h \
    winwindow.h \
    losewindow.h

FORMS += \
    mainwindow.ui \
    settingwindow.ui \
    winwindow.ui \
    losewindow.ui


RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += $$PWD/../Course/CourseLib
DEPENDPATH += $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/libCourseLib.a
