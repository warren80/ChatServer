#-------------------------------------------------
#
# Project created by QtCreator 2011-03-02T10:21:43
#
#-------------------------------------------------

QT       += core gui

TARGET = ChatServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        textClient.cpp \
        textServer.cpp \
    settings.cpp


HEADERS  += mainwindow.h \
         += textClient.h \
         += textServer.h \
    settings.h

FORMS    += mainwindow.ui \
    settings.ui
