#-------------------------------------------------
#
# Project created by QtCreator 2015-01-18T12:53:06
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = FYP_BETA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    control.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    control.h \
    qcustomplot.h

FORMS    += mainwindow.ui
