#-------------------------------------------------
#
# Project created by QtCreator 2014-06-10T09:41:42
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Protocole
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc


SOURCES += main.cpp \
    menu.cpp \
    fullwindow.cpp \
    video.cpp \
    centralwidget.cpp \
    videoswidget.cpp

HEADERS += \
    menu.h \
    fullwindow.h \
    video.h \
    centralwidget.h \
    define.h \
    videoswidget.h
