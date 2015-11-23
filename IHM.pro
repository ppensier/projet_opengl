#-------------------------------------------------
#
# Project created by QtCreator 2014-11-18T07:50:11
#
#-------------------------------------------------

QT      += core gui
QT      += opengl
QT +=   xml

LIBS += -lQGLViewer
LIBS += -lglut
LIBS += -lGLU
INCLUDEPATH += -L/usr/lib/

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    triangle.cpp \
    simpleViewer.cpp \
    droite.cpp \
    plan.cpp \
    minitab.cpp

HEADERS  += mainwindow.h \
    triangle.h \
    simpleViewer.h \
    droite.h \
    plan.h \
    minitab.h

FORMS    += mainwindow.ui
