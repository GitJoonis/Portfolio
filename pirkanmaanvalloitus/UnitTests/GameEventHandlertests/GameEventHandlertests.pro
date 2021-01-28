QT += testlib
QT += gui
QT += core gui widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG += app_bundle

TEMPLATE = app

SOURCES +=  tst_gameeventhandlertests.cpp \
    ../../Game/handlers/gameeventhandler.cpp

HEADERS += \
    ../../Game/handlers/gameeventhandler.h \

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += -L$$OUT_PWD/../../Course/CourseLib/ -lCourseLib

INCLUDEPATH += $$PWD/../../Course/CourseLib
DEPENDPATH += $$PWD/../../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/libCourseLib.a

