/****************************************************************************
** Meta object code from reading C++ file 'clientsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../clientsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClientSocket_t {
    QByteArrayData data[12];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientSocket_t qt_meta_stringdata_ClientSocket = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ClientSocket"
QT_MOC_LITERAL(1, 13, 11), // "displayMess"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 1), // "m"
QT_MOC_LITERAL(4, 28, 13), // "sigDisconnect"
QT_MOC_LITERAL(5, 42, 13), // "slotConnected"
QT_MOC_LITERAL(6, 56, 9), // "slotError"
QT_MOC_LITERAL(7, 66, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(8, 95, 3), // "err"
QT_MOC_LITERAL(9, 99, 13), // "slotReadyRead"
QT_MOC_LITERAL(10, 113, 15), // "slotDisplayMess"
QT_MOC_LITERAL(11, 129, 16) // "slotDisconnected"

    },
    "ClientSocket\0displayMess\0\0m\0sigDisconnect\0"
    "slotConnected\0slotError\0"
    "QAbstractSocket::SocketError\0err\0"
    "slotReadyRead\0slotDisplayMess\0"
    "slotDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   53,    2, 0x0a /* Public */,
       6,    1,   54,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,
      10,    1,   58,    2, 0x0a /* Public */,
      11,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

       0        // eod
};

void ClientSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientSocket *_t = static_cast<ClientSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->displayMess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sigDisconnect(); break;
        case 2: _t->slotConnected(); break;
        case 3: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->slotReadyRead(); break;
        case 5: _t->slotDisplayMess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->slotDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClientSocket::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientSocket::displayMess)) {
                *result = 0;
            }
        }
        {
            typedef void (ClientSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientSocket::sigDisconnect)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ClientSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientSocket.data,
      qt_meta_data_ClientSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ClientSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ClientSocket.stringdata0))
        return static_cast<void*>(const_cast< ClientSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int ClientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ClientSocket::displayMess(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientSocket::sigDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
