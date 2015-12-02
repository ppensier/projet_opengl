#-------------------------------------------------
#
# Project created by QtCreator 2014-11-18T07:50:11
#
#-------------------------------------------------

QT      += core gui
QT      += opengl
QT +=   xml

LIBS += -lQGLViewer
INCLUDEPATH += -L/usr/lib/

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    simpleViewer.cpp \
    droite.cpp \
    plan.cpp \
    mnt.cpp \
    parabole.cpp \
    threadhorizontal.cpp \
    threadvertical.cpp \
    threadoblique.cpp

HEADERS  += mainwindow.h \
    simpleViewer.h \
    droite.h \
    plan.h \
    mnt.h \
    parabole.h \
    threadhorizontal.h \
    threadvertical.h \
    threadoblique.h

FORMS    += mainwindow.ui
