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
    QString buffer;
    int BytesToRead;
    int BytesReaded;
public:
    tcpclient();
    void connect_(QString addr, int Port);
    void sendData(QString document);
    QString processData(QString str);
public slots:
    void readData();
    void slotConnected();
    void slotError(QAbstractSocket::SocketError err);
    void slotDisconect();
signals:
    void GetData(QString msg);
    void errormess(QString mess);
    void sig_disconnect();
    void sig_connected();
};

#endif // TCPCLIENT_H
