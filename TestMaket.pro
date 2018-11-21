#-------------------------------------------------
#
# Project created by QtCreator 2016-10-26T15:37:43
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestMaket
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    screenshotmaker.cpp \
    snapprocess.cpp \
    srvapi.cpp \
    hook.cpp \
    loginform.cpp

HEADERS  += \
    mainwindow.h \
    screenshotmaker.h \
    snapprocess.h \
    srvapi.h \
    hook.h \
    hook_global.h \
    loginform.h

FORMS    += \
    mainwindow.ui \
    loginform.ui

RESOURCES += \
    resurs.qrc

DEFINES += HOOK_LIBRARY

