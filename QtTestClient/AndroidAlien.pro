#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T20:58:58
#
#-------------------------------------------------

QT       += core gui network xml
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AndroidAlien
TEMPLATE = app


SOURCES += tcpclient.cpp \
    xmlmanager.cpp \
    alienclient.cpp \
    ui/game.cpp \
    ui/lobby.cpp \
    ui/lobbyregistername.cpp \
    ui/lobbyregisterrole.cpp \
    ui/lobbywaiting.cpp \
    ui/mainwindow.cpp \
    ui/playerlist.cpp \
    ui/playerwidget.cpp \
    ui/start.cpp \
    main.cpp \
    xmlprotocol.cpp \
    ui/actions.cpp \
    ui/inventory.cpp \
    ui/log.cpp \
    ui/status.cpp \
    ui/targets.cpp

HEADERS  += tcpclient.h \
    xmlmanager.h \
    alienclient.h \
    ui/game.h \
    ui/lobby.h \
    ui/lobbyregistername.h \
    ui/lobbyregisterrole.h \
    ui/lobbywaiting.h \
    ui/mainwindow.h \
    ui/playerlist.h \
    ui/playerwidget.h \
    ui/start.h \
    xmlprotocol.h \
    types.h \
    ui/actions.h \
    ui/inventory.h \
    ui/log.h \
    ui/status.h \
    ui/targets.h

FORMS    += \
    ui/game.ui \
    ui/lobby.ui \
    ui/lobbyregistername.ui \
    ui/lobbyregisterrole.ui \
    ui/lobbywaiting.ui \
    ui/mainwindow.ui \
    ui/playerlist.ui \
    ui/playerwidget.ui \
    ui/start.ui \
    ui/actions.ui \
    ui/inventory.ui \
    ui/log.ui \
    ui/status.ui \
    ui/targets.ui
