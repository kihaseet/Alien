#ifndef _MyClient_h_
#define _MyClient_h_

#include <QtGui>
#include <QtCore>
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QList>
#include <QMap>
#include <QTcpSocket>
#include "clientsocket.h"

//class QTextEdit;
//class QLineEdit;

class MyClient : public QWidget {

    Q_OBJECT

private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit* m_ptxtInfo;
    QLineEdit* m_pnameInput;
    QLineEdit* m_ptxtInput;
    quint16 m_nNextBlockSize;
    QString m_name;
    QMap <QString,ClientSocket*> clients;



public:
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0) ;
    ClientSocket* Qu;
    ClientSocket* Ermon;
    ClientSocket* Wendy;
    ClientSocket* Helen;
    ClientSocket* Rick;
    ClientSocket* Tau;
    ClientSocket* Ygg;
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
    void slotUB();
    void voteAll();
    void waitAll();
    void slotn1();
    void slotn2();
    void slotn3();
    void slotn4();
    void slotn5();
    void slotn6();
    void slotn7();
    void slotDisplay(QString m);
    //  void slotDisonnected  ();
    void slotConnecting();
    void slotDisconnected();
};

#endif //_MyClient_h_
