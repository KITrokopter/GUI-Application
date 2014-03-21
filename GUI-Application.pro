#-------------------------------------------------
#
# Project created by QtCreator 2014-03-03T17:35:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI-Application
TEMPLATE = app

INCLUDEPATH = C:\Qt\Tools\mingw48_32\include
LIBS += -lSDL2


SOURCES += main.cpp\
        mainwindow.cpp \
    quadcoptermodel.cpp \
    quadcopterdebugdialog.cpp \
    quadcoptertrackedfilter.cpp \
    quadcopterdetaildialog.cpp \
    calibrationdialog.cpp \
    singlecalibrationwidget.cpp \
    cameramodel.cpp \
    gamepad.cpp \
    movementcontroller.cpp \
    globalcalibrationwidget.cpp \
    gamepaddebugdialog.cpp \
    aboutdialog.cpp \
    irrlichtwidget.cpp

HEADERS  += mainwindow.hpp \
    quadcoptermodel.hpp \
    quadcopterdebugdialog.hpp \
    quadcoptertrackedfilter.hpp \
    quadcopterdetaildialog.hpp \
    calibrationdialog.hpp \
    singlecalibrationwidget.hpp \
    cameramodel.hpp \
    gamepad.hpp \
    movementcontroller.hpp \
    globalcalibrationwidget.hpp \
    gamepaddebugdialog.hpp \
    aboutdialog.hpp \
    irrlichtwidget.hpp

FORMS    += mainwindow.ui \
    quadcopterdebugdialog.ui \
    quadcopterdetaildialog.ui \
    calibrationdialog.ui \
    singlecalibrationwidget.ui \
    globalcalibrationwidget.ui \
    gamepaddebugdialog.ui \
    aboutdialog.ui
