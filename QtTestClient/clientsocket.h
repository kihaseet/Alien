#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include<QtCore>
#include<qtcpsocket.h>
#include<QtNetwork>
#include<QObject>

class QTcpSocket;

class ClientSocket : public QObject
{
Q_OBJECT

public:
    static QMap <QString, QString> NameRole;
    static QMap<QString, QString> initColumnNames();

    QTcpSocket* _socket;
    QString _name;
    ClientSocket(QString name);
    Send(QString mes);
    SendNameToServer();


public slots:
    void slotConnected();
    void slotError(QAbstractSocket::SocketError err);
    void slotReadyRead();
    void slotDisplayMess(QString m);
    void slotDisconnected();
signals:
    void displayMess(QString m);
    void sigDisconnect();
};

#endif // CLIENTSOCKET_H
