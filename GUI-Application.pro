#-------------------------------------------------
#
# Project created by QtCreator 2014-03-03T17:35:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI-Application
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    quadcoptermodel.cpp \
    quadcopterdebugdialog.cpp

HEADERS  += mainwindow.hpp \
    quadcoptermodel.hpp \
    quadcopterdebugdialog.hpp

FORMS    += mainwindow.ui \
    quadcopterdebugdialog.ui
