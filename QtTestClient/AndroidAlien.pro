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


SOURCES += main.cpp \
    gameclient.cpp \
    types/action.cpp \
    types/itarget.cpp \
    types/player.cpp \
    types/currentplayer.cpp \
    types/item.cpp \
    factories/actionfactory.cpp \
    events/ievent.cpp \
    events/eventitem.cpp \
    events/eventstatus.cpp \
    events/eventrole.cpp \
    events/eventvoting.cpp \
    factories/eventfactory.cpp \
    types/vote.cpp \
    types/endvote.cpp \
    statupdate/istatupdate.cpp \
    statupdate/statadditem.cpp \
    statupdate/statdelitem.cpp \
    statupdate/statalien.cpp \
    statupdate/statchangehp.cpp \
    factories/statupdatefactory.cpp \
    protocol/iprotocol.cpp \
    protocol/xmlprotocol/xmlprotocol.cpp \
    protocol/tcpclient.cpp \
    mainwindow.cpp \
    events/eventduty.cpp \
    statupdate/statuseditem.cpp \
    types/status.cpp \
    qclickablelabel.cpp \
    gametabs.cpp

HEADERS  += gameclient.h \
    types/action.h \
    types/itarget.h \
    types/player.h \
    types/currentplayer.h \
    types/item.h \
    factories/actionfactory.h \
    events/ievent.h \
    events/eventitem.h \
    events/eventstatus.h \
    events/eventrole.h \
    events/eventvoting.h \
    factories/eventfactory.h \
    types/vote.h \
    types/endvote.h \
    statupdate/istatupdate.h \
    statupdate/statadditem.h \
    statupdate/statdelitem.h \
    statupdate/statalien.h \
    statupdate/statchangehp.h \
    factories/statupdatefactory.h \
    protocol/iprotocol.h \
    protocol/xmlprotocol/xmlprotocol.h \
    protocol/tcpclient.h \
    mainwindow.h \
    types/status.h \
    types/playerimage.h \
    types/itemtype.h \
    types/actiontype.h \
    events/eventduty.h \
    statupdate/statuseditem.h \
    qclickablelabel.h \
    gametabs.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    alienresources.qrc
