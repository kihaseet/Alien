#ifndef _MyClient_h_
#define _MyClient_h_

#include <QWidget>
#include <QTcpSocket>
#include "clientsocket.h"

class QTextEdit;
class QLineEdit;

class MyClient : public QWidget {

    Q_OBJECT

private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit* m_ptxtInfo;
    QLineEdit* m_pnameInput;
    QLineEdit* m_ptxtInput;
    quint16 m_nNextBlockSize;
    QString m_name;
    QList <ClientSocket*> clients;

public:
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0) ;
    void SendNameToServer(ClientSocket *a, QString n);
    void SendToServerMsg(ClientSocket* a, QString msg);
public slots:
    void slotUI();
    void slotUU();
    void slotAT();
    void slotIN();
    void slotWA();
    void slotUP();
    void slotDO();
    void slotVO();
    void slotUN();
private slots:
    void slotReadyRead  ();
    void slotError      (QAbstractSocket::SocketError); void slotSendToServer();
    void slotConnected  ();
    void slotConnecting ();
  //  void slotDisonnected  ();
};
#endif //_MyClient_h_
