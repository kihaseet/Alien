#include "clientsocket.h"

ClientSocket::ClientSocket(QTcpSocket *socket, int name)
{
    _socket=socket;
    //if(name!="")
        _name=name;
}
