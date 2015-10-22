#-------------------------------------------------
#
# Project created by QtCreator 2014-11-18T07:50:11
#
#-------------------------------------------------

QT      += core gui
QT      += opengl

LIBS += -lglut
LIBS += -lGLU
INCLUDEPATH += -L/usr/lib/

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        points.cpp \
    myglwidget.cpp \
    triangle.cpp

HEADERS  += mainwindow.h \
        points.h \
    myglwidget.h \
    triangle.h

FORMS    += mainwindow.ui
