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
        socket.cpp \
        settings.cpp \
    thread.cpp \
    component.cpp

HEADERS  += mainwindow.h \
          textClient.h \
          textServer.h \
          socket.h \
          settings.h \
    includes.h \
    thread.h \
    component.h

FORMS    += mainwindow.ui \
         settings.ui
