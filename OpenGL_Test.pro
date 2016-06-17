#-------------------------------------------------
#
# Project created by QtCreator 2016-04-11T14:44:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = OpenGL_Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myopenglwidget.cpp \
    renderer.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    myopenglwidget.h \
    renderer.h \
    qcustomplot.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
