#include "clientsocket.h"

QMap<QString, QString> ClientSocket::initColumnNames()
{


    QMap<QString, QString> map;
    map.insert("Qu","Captain");
    map.insert("Ermon","Assistant");
    map.insert("Wendy","Doctor");
    map.insert("Helen","Gunmen");
    map.insert("Rick","Engineer");
    map.insert("Tau","Scientist");
    map.insert("Ygg","Signalmen");
    return map;
}

ClientSocket::ClientSocket(QString name)
{
    _socket = new QTcpSocket();;
    _name = name;

    connect(_socket, SIGNAL(connected()),this, SLOT(slotConnected()));
    connect(_socket, SIGNAL(readyRead()), this,SLOT(slotReadyRead()));
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(slotError(QAbstractSocket::SocketError))
            );
    connect(_socket, SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}

ClientSocket::Send(QString mes)
{
    QString tmp = mes +'\n'+'\n';
    QByteArray data = tmp.toLocal8Bit();
    _socket->write(data);
}

ClientSocket::SendNameToServer()
{
    this->Send("<!DOCTYPE selecting><selecting><regname>" + this->_name + "</regname></selecting>");
    this->Send("<!DOCTYPE selecting><selecting><regrole>" + NameRole.value(this->_name) + "</regrole></selecting>");
}

void ClientSocket::slotConnected()
{
    SendNameToServer();
}


void ClientSocket::slotError(QAbstractSocket::SocketError err)
{
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host was not found." :
                                                                                QString(this->_socket->errorString()) );
    slotDisplayMess(strError);
}

void ClientSocket::slotReadyRead()
{
    if(((QTcpSocket*)sender())->canReadLine()){
        QByteArray data = ((QTcpSocket*)sender())->readAll();
        QString tmp = data.data();
        tmp=tmp.trimmed();//полученное сообщение
        QStringList m = tmp.split("\n\n");

        foreach (QString var, m) {
            slotDisplayMess ("[" +_name + "]" + var);
        }
    }
}

void ClientSocket::slotDisplayMess(QString m)
{
    emit displayMess(m);
}

void ClientSocket::slotDisconnected()
{
    emit sigDisconnect();
    this->deleteLater();
}

QMap <QString, QString> ClientSocket::NameRole = initColumnNames();
