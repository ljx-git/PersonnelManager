#-------------------------------------------------
#
# Project created by QtCreator 2017-06-12T18:41:11
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = personnelManager
TEMPLATE = app


SOURCES += main.cpp \
    manager.cpp \
    login.cpp \
    user.cpp

HEADERS  += \
    manager.h \
    login.h \
    user.h

FORMS    += \
    manager.ui \
    login.ui \
    user.ui

RESOURCES += \
    resouce.qrc
