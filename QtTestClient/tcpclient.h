#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QtNetwork>

class tcpclient: public QObject
{
    Q_OBJECT
private:
    QTcpSocket* serv;
    QString nHost;
    int nPort;
public:
    tcpclient(int Port);
public slots:
    void sendData(QString document);
    void readData();
    void slotConnected();
    void slotError(QAbstractSocket::SocketError err);
    void slotConnecting(QString addr);
    void slotDisconect();
signals:
    void GetData(QString msg);
    void errormess(QString mess);
    void disconnect();
};

#endif // TCPCLIENT_H
