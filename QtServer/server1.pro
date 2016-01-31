#-------------------------------------------------
#
# Project created by QtCreator 2014-10-26T02:04:19
#
#-------------------------------------------------

QT       +=  core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

targets = server1
TEMPLATE = app

CONFIG += warn_off

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
    types.cpp \
    proto/client.pb.cc \
    proto/server.pb.cc \
    proto/types.pb.cc \
    proto/protobuf_maker.cpp

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
    protocol.h \
    proto/client.pb.h \
    proto/server.pb.h \
    proto/types.pb.h \
    proto/protobuf_maker.h

FORMS    += mainwindow.ui \
    config.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lprotobuf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lprotobufd

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/libprotobuf.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/libprotobufd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/protobuf.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/protobufd.lib
