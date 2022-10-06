#-------------------------------------------------
#
# Project created by QtCreator 2022-09-25T23:24:53
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plane_war
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

RC_FILE=appico.rc     #设置软件图标

SOURCES += \
        main.cpp \
        widget.cpp \
    map.cpp \
    plane.cpp \
    bullet.cpp \
    em_plane.cpp \
    mainwidget.cpp

HEADERS += \
        widget.h \
    map.h \
    config.h \
    plane.h \
    bullet.h \
    em_plane.h \
    mainwidget.h

RESOURCES += \
    res.qrc
