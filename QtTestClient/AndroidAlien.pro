#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T20:58:58
#
#-------------------------------------------------

QT       += core gui network xml

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
    xmlprotocol.cpp

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
    xmlprotocol.h

FORMS    += ui/form.ui \
    ui/game.ui \
    ui/lobby.ui \
    ui/lobbyregistername.ui \
    ui/lobbyregisterrole.ui \
    ui/lobbywaiting.ui \
    ui/mainwindow.ui \
    ui/playerlist.ui \
    ui/playerwidget.ui \
    ui/start.ui
