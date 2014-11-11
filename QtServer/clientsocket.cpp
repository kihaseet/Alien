#include "clientsocket.h"

ClientSocket::ClientSocket(QTcpSocket *socket, QString name = QString())
{
    _socket=socket;
    if(name!="") _name=name;
}
