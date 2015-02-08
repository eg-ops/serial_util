#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T21:26:37
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serial_util
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workerthread.cpp

HEADERS  += mainwindow.h \
    workerthread.h

FORMS    += mainwindow.ui
