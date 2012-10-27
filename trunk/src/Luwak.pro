#-------------------------------------------------
#
# Project created by QtCreator 2012-10-22T11:39:39
#
# Don't forget to clean after using
#-------------------------------------------------

QT       += core gui

TARGET = Luwak
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imgconvert.cpp \
    iqgraphicsscene.cpp

HEADERS  += mainwindow.h \
    imgconvert.h \
    iqgraphicsscene.h

FORMS    += mainwindow.ui

CONFIG += link_pkgconfig
PKGCONFIG += opencv
