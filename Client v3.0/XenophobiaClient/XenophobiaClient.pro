TEMPLATE = app

QT += qml quick

CONFIG += warn_off

SOURCES += main.cpp \
    gamewindow.cpp \
    proto/client.pb.cc \
    proto/server.pb.cc \
    proto/types.pb.cc \
    models/rolesmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    gamewindow.h \
    proto/client.pb.h \
    proto/server.pb.h \
    proto/types.pb.h \
    models/rolesmodel.h

win32:CONFIG(release, debug|release): LIBS += -LE:/libs/protobuf/lib/ -lprotobuf
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/libs/protobuf/lib/ -lprotobufd

INCLUDEPATH += E:/libs/protobuf
DEPENDPATH += E:/libs/protobuf
