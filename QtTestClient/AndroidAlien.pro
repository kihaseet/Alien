#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T20:58:58
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AndroidAlien
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lobby.cpp \
    game.cpp \
    tcpclient.cpp \
    start.cpp \
    xmlmanager.cpp \
    lobbyregistername.cpp \
    lobbyregisterrole.cpp \
    lobbywaiting.cpp \
    playerlist.cpp \
    playerwidget.cpp

HEADERS  += mainwindow.h \
    lobby.h \
    tcpclient.h \
    start.h \
    xmlmanager.h \
    lobbyregistername.h \
    lobbyregisterrole.h \
    lobbywaiting.h \
    game.h \
    playerlist.h \
    playerwidget.h

FORMS    += mainwindow.ui \
    lobby.ui \
    game.ui \
    start.ui \
    lobbyregistername.ui \
    lobbyregisterrole.ui \
    lobbywaiting.ui \
    playerlist.ui \
    playerwidget.ui
