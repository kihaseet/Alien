#-------------------------------------------------
#
# Project created by QtCreator 2014-10-26T02:04:19
#
#-------------------------------------------------

QT       +=  core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server1
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    server.cpp \
    xml_maker.cpp \
    player.cpp \
    item.cpp \
    voting.cpp \
    event.cpp \
    clientsocket.cpp \
    config.cpp \
    types.cpp

HEADERS  += mainwindow.h \
    game.h \
    server.h \
    xml_maker.h \
    player.h \
    item.h \
    voting.h \
    event.h \
    clientsocket.h \
    config.h \
    types.h \
    protocol.h

FORMS    += mainwindow.ui \
    config.ui
