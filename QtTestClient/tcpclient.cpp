#include "tcpclient.h"


tcpclient::tcpclient()
{
    serv = new QTcpSocket();
    connect(serv, SIGNAL(connected()),this, SLOT(slotConnected()));
    connect(serv, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(slotError(QAbstractSocket::SocketError)));

    connect(serv,SIGNAL(readyRead()),SLOT(readData()));
}

void tcpclient::sendData(QString document)
{
    QString tmp = document +'\n';
    QByteArray data = tmp.toLocal8Bit();
    serv->write(data);
}

void tcpclient::readData()
{
    if(((QTcpSocket*)sender())->canReadLine()){
        QByteArray data = ((QTcpSocket*)sender())->readAll();
        QString tmp = data.data();
        tmp=tmp.trimmed();//полученное сообщение
        emit GetData(tmp);
    }
}

void tcpclient::slotError(QAbstractSocket::SocketError err)
{
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host was not found." :
           err == QAbstractSocket::RemoteHostClosedError ? "The remote host is closed." :
           err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused." :
                                                            QString(serv->errorString()) );
    emit errormess(strError);
}

void tcpclient::slotConnected()
{
    emit errormess("Loading player's list...");
}

void tcpclient::connect(QString addr, int Port){
    this->nPort = Port;
    serv->connectToHost(addr,Port);
}

void tcpclient::slotDisconect(){
    emit disconnect();
}

