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
    tcpclient();
    void connect(QString addr, int Port);
    void sendData(QString document);
public slots:
    void readData();
    void slotConnected();
    void slotError(QAbstractSocket::SocketError err);
    void slotDisconect();
signals:
    void GetData(QString msg);
    void errormess(QString mess);
    void disconnect();
};

#endif // TCPCLIENT_H
