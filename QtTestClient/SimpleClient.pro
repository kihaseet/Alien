QT += core gui network  testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
SOURCES += \
    main.cpp \
    MyClient.cpp \
    clientsocket.cpp

HEADERS += \
    MyClient.h \
    clientsocket.h
