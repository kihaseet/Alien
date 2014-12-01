#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include<QtCore>

class QTcpSocket;

class ClientSocket
{
public:
    QTcpSocket* _socket;
    QString _name;
    ClientSocket(QTcpSocket* socket,QString name);
};

#endif // CLIENTSOCKET_H
