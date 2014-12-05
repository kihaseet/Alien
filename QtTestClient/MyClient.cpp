#include <QTime>
#include <QtNetwork>
#include <QtGui>
#include <QDebug>
#include "myclient.h"
#include <QtTest/QTest>

MyClient::MyClient(const QString& strHost,
                   int nPort,
                   QWidget* pwgt /*=0*/) : QWidget(pwgt)
  , m_nNextBlockSize(0)
{

    //m_pTcpSocket = new QTcpSocket(this);
    for(int i=1;i<8;i++){
        // QTest::qWait(10);
        ClientSocket* a = new ClientSocket(new QTcpSocket(),QString::number(i));


        connect(a->_socket, SIGNAL(connected()),this, SLOT(slotConnected()));
        connect(a->_socket, SIGNAL(readyRead()), this,SLOT(slotReadyRead()));
        connect(a->_socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
                SLOT(slotError(QAbstractSocket::SocketError))
                );
        clients.append(a);
    }
    //    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    //    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    //    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
    //            SLOT(slotError(QAbstractSocket::SocketError))
    //            );

    m_ptxtInfo = new QTextEdit;
    m_ptxtInput = new QLineEdit;
    m_pnameInput = new QLineEdit;
    m_ptxtInfo->setReadOnly(true);

    QPushButton* pcmd = new QPushButton("&Send");
    QPushButton* pcon = new QPushButton("&Connect");

    QPushButton* pcui = new QPushButton("&use item");
    QPushButton* pcuu = new QPushButton("&use ult");
    QPushButton* pcub = new QPushButton("&ult badge");
    QPushButton* pcat = new QPushButton("&attack");
    QPushButton* pcin = new QPushButton("&infect");
    QPushButton* pcwa = new QPushButton("&wait");
    QPushButton* pcup = new QPushButton("&up");
    QPushButton* pcdo = new QPushButton("&down");
    QPushButton* pcvo = new QPushButton("&vote");
    QPushButton* pcun = new QPushButton("&unvote");


    connect(pcmd, SIGNAL(clicked()),SLOT(slotSendToServer()));
    connect(pcon, SIGNAL(clicked()),SLOT(slotConnecting()));
    //connect(m_ptxtInput, SIGNAL(returnPressed()),this, SLOT(slotSendToServer()));

    connect(pcui, SIGNAL(clicked()),SLOT(slotUI()));
    connect(pcuu, SIGNAL(clicked()),SLOT(slotUU()));
    connect(pcat, SIGNAL(clicked()),SLOT(slotAT()));
    connect(pcin, SIGNAL(clicked()),SLOT(slotIN()));
    connect(pcwa, SIGNAL(clicked()),SLOT(slotWA()));
    connect(pcup, SIGNAL(clicked()),SLOT(slotUP()));
    connect(pcdo, SIGNAL(clicked()),SLOT(slotDO()));
    connect(pcvo, SIGNAL(clicked()),SLOT(slotVO()));
    connect(pcun, SIGNAL(clicked()),SLOT(slotUN()));
    connect(pcub, SIGNAL(clicked()),SLOT(slotUB()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    QHBoxLayout* phbxLayout = new QHBoxLayout;

    QHBoxLayout* H1 = new QHBoxLayout;
    QHBoxLayout* H2 = new QHBoxLayout;
    QHBoxLayout* H3 = new QHBoxLayout;

    H1->addWidget(pcui);
    H1->addWidget(pcuu);
    H1->addWidget(pcat);
    H2->addWidget(pcin);
    H2->addWidget(pcwa);
    H2->addWidget(pcup);
    H3->addWidget(pcdo);
    H3->addWidget(pcvo);
    H3->addWidget(pcun);


    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));

    phbxLayout->addWidget(new QLabel("Nickname"));

    phbxLayout->addWidget(m_pnameInput);
    phbxLayout->addWidget(pcon);
    pvbxLayout->addLayout(phbxLayout);
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addLayout(H1);
    pvbxLayout->addLayout(H2);
    pvbxLayout->addLayout(H3);
    pvbxLayout->addWidget(pcub);
    pvbxLayout->addWidget(pcmd);

    setLayout(pvbxLayout);
}

void MyClient::slotReadyRead()
{
    QDataStream in((QTcpSocket*)sender());
    in.setVersion(QDataStream::Qt_4_5); for (;;) {
        if (!m_nNextBlockSize) {
            if (((QTcpSocket*)sender())->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (((QTcpSocket*)sender())->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime  time; QString str;
        in >> str;
        //qDebug()<<str;
        //  m_ptxtInfo->append(str); m_nNextBlockSize = 0;
    }
}

void MyClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host was not found." :
                                                                                err == QAbstractSocket::RemoteHostClosedError ? "The remote host is closed." :
                                                                                                                                err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused." :
                                                                                                                                                                                 QString(m_pTcpSocket->errorString()) );
    m_ptxtInfo->append(strError);
}


void MyClient::slotSendToServer()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly); out.setVersion(QDataStream::Qt_4_5);
    //out << quint16(0) << QTime::currentTime() << m_ptxtInput->text();
    out << quint16(0) << m_ptxtInput->text();
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    foreach (ClientSocket* var, clients) {
        if(var->_name==m_pnameInput->text()){
            var->_socket->write(arrBlock);
            m_ptxtInput->setText("");
        }
    }
    //m_pTcpSocket->write(arrBlock); m_ptxtInput->setText("");
}

void MyClient::SendNameToServer(ClientSocket* a,QString n)
{
    // QTest::qWait(10);

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly); out.setVersion(QDataStream::Qt_4_5);
    //out << quint16(0) << QTime::currentTime() << m_ptxtInput->text();
    QString msg = "<!DOCTYPE selecting><selecting><regname>"+a->_name+"</regname></selecting>";
    out << quint16(0) << msg;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    a->_socket->write(arrBlock);
    // QTest::qWait(100);
    if(n=="1"){
        msg = "<!DOCTYPE selecting><selecting><regrole>Captain</regrole></selecting>";
        SendToServerMsg(a,msg);
    }
    if(n=="2"){
        msg = "<!DOCTYPE selecting><selecting><regrole>Doctor</regrole></selecting>";
        SendToServerMsg(a,msg);
    }
    if(n=="3"){
        msg = "<!DOCTYPE selecting><selecting><regrole>Gunmen</regrole></selecting>";
        SendToServerMsg(a,msg);
    }
    if(n=="4"){
        msg = "<!DOCTYPE selecting><selecting><regrole>Assistant</regrole></selecting>";
        SendToServerMsg(a,msg);
    }
    if(n=="5"){
        msg = "<!DOCTYPE selecting><selecting><regrole>Engineer</regrole></selecting>";
        SendToServerMsg(a,msg);
    }
    if(n=="6"){
        msg = "<!DOCTYPE selecting><selecting><regrole>Scientist</regrole></selecting>";
        SendToServerMsg(a,msg);
    }
    if(n=="7"){
        msg = "<!DOCTYPE selecting><selecting><regrole>Signalmen</regrole></selecting>";
        SendToServerMsg(a,msg);
    }
}

void MyClient::SendToServerMsg(ClientSocket* a, QString msg)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly); out.setVersion(QDataStream::Qt_4_5);
    //out << quint16(0) << QTime::currentTime() << m_ptxtInput->text();
    out << quint16(0) << msg;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    a->_socket->write(arrBlock); m_ptxtInput->setText("");
}

void MyClient::slotConnected()
{

    foreach (ClientSocket* car, clients) {
        if(car->_socket==sender()){
            m_ptxtInfo->append("Received the connected() signal");
            SendNameToServer(car,car->_name);
        }
    }
    //SendNameToServer();
}

void MyClient::slotUI(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE changing><changing><use item=\"Battery\">Blaster</use></changing>");
}

void MyClient::slotUU(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE changing><changing><use ult=\"Battery\">Blaster</use></changing>");
}

void MyClient::slotAT(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE changing><changing><attack>Piggy</attack></changing>");
}

void MyClient::slotIN(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE changing><changing><infect>Piggy</infect></changing>");
}

void MyClient::slotWA(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE changing><changing><wait/></changing>");
}

void MyClient::slotUP(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE changing><changing><up/></changing>");
}

void MyClient::slotDO(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE changing><changing><down/></changing>");
}

void MyClient::slotVO(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE voting><voting><vote>Piggy</vote></voting>");
}

void MyClient::slotUN(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE voting><voting><unvote/></voting>");
}

void MyClient::slotUB(){
    m_ptxtInput->clear();
    m_ptxtInput->setText("<!DOCTYPE changing><changing><use badge=\"Battery\">Blaster</use></changing>");
}

void MyClient::slotConnecting(){
    foreach (ClientSocket* var, clients) {
        var->_socket->connectToHost("localhost", 21277);
        // QTest::qWait(10);

        // QTest::qWait(10);
    }
    // m_pTcpSocket->connectToHost("localhost", 21277);
    //разворачиваем ядерный пиздец!

}
