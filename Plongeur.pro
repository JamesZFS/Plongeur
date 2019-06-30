#-------------------------------------------------
#
# Project created by QtCreator 2019-05-17T15:30:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Plongeur
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
        main.cpp \
        mainwindow.cpp \
        gameframe.cpp \
        statdialog.cpp \
    gamescene.cpp \
    constants.cpp \
    actor.cpp \
    diver.cpp \
    pool.cpp \
    engine.cpp \
    water.cpp \
    contactlistener.cpp

HEADERS += \
        mainwindow.h \
        gameframe.h \
        statdialog.h \
    gamescene.h \
    constants.h \
    actor.h \
    diver.h \
    pool.h \
    engine.h \
    water.h \
    contactlistener.h

FORMS += \
        mainwindow.ui \
        gameframe.ui \
        statdialog.ui

RESOURCES += \
        res.qrc

# *** the below is the INCLUDE PATH and LIBRARY PATH of liquidfun, you should
# change it to the liquidfun path on your computer, or the compilation won't work.
INCLUDEPATH += \
    /Users/rachelmao/Desktop/liquidfun-master/liquidfun/Box2D

LIBS += \
    /Users/rachelmao/Desktop/liquidfun-master/liquidfun/Box2D/Box2D/Debug/libliquidfun.a
