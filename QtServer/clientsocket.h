#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include<QtCore>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QDebug>
#include <QUdpSocket>
#include <QObject>

class QTcpSocket;

class ClientSocket
{
public:
    QTcpSocket* _socket;
    int _name;
    ClientSocket(QTcpSocket* socket,int name);
};

#endif // CLIENTSOCKET_H
