#include <QTime>
#include <QtNetwork>
#include <QtGui>
#include <QDebug>
#include "myclient.h"
#include <QTimer>

MyClient::MyClient(const QString& strHost,
                   int nPort,
                   QWidget* pwgt /*=0*/) : QWidget(pwgt)
  , m_nNextBlockSize(0)
{

    m_ptxtInfo = new QTextEdit;
    m_ptxtInput = new QLineEdit;
    m_pnameInput = new QLineEdit;
    m_ptxtInfo->setReadOnly(true);

    QPushButton* pcn1 = new QPushButton("&1");
    QPushButton* pcn2 = new QPushButton("&2");
    QPushButton* pcn3 = new QPushButton("&3");
    QPushButton* pcn4 = new QPushButton("&4");
    QPushButton* pcn5 = new QPushButton("&5");
    QPushButton* pcn6 = new QPushButton("&6");
    QPushButton* pcn7 = new QPushButton("&7");

    pcn1->setMaximumWidth(30);
    pcn2->setMaximumWidth(30);
    pcn3->setMaximumWidth(30);
    pcn4->setMaximumWidth(30);
    pcn5->setMaximumWidth(30);
    pcn6->setMaximumWidth(30);
    pcn7->setMaximumWidth(30);

    QPushButton* pcmd = new QPushButton("&Send");
    QPushButton* pcva = new QPushButton("&Vote all");
    QPushButton* pcww = new QPushButton("&Wait all");
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
    connect(pcva,SIGNAL(clicked()),SLOT(voteAll()));
    connect(pcww,SIGNAL(clicked()),SLOT(waitAll()));

    connect(pcn1, SIGNAL(clicked()),SLOT(slotn1()));
    connect(pcn2, SIGNAL(clicked()),SLOT(slotn2()));
    connect(pcn3, SIGNAL(clicked()),SLOT(slotn3()));
    connect(pcn4, SIGNAL(clicked()),SLOT(slotn4()));
    connect(pcn5, SIGNAL(clicked()),SLOT(slotn5()));
    connect(pcn6, SIGNAL(clicked()),SLOT(slotn6()));
    connect(pcn7, SIGNAL(clicked()),SLOT(slotn7()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    QHBoxLayout* phbxLayout = new QHBoxLayout;

    QHBoxLayout* H0 = new QHBoxLayout;

    QHBoxLayout* H1 = new QHBoxLayout;
    QHBoxLayout* H2 = new QHBoxLayout;
    QHBoxLayout* H3 = new QHBoxLayout;

    H0->addWidget(pcn1);
    H0->addWidget(pcn2);
    H0->addWidget(pcn3);
    H0->addWidget(pcn4);
    H0->addWidget(pcn5);
    H0->addWidget(pcn6);
    H0->addWidget(pcn7);

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
    pvbxLayout->addLayout(H0);
    pvbxLayout->addLayout(H1);
    pvbxLayout->addLayout(H2);
    pvbxLayout->addLayout(H3);
    pvbxLayout->addWidget(pcub);
    pvbxLayout->addWidget(pcmd);
    pvbxLayout->addWidget(pcva);
    pvbxLayout->addWidget(pcww);

    setLayout(pvbxLayout);
}



void MyClient::voteAll()
{
    /* foreach (QTcpSocket* var, clients) {
        QString msg = "<!DOCTYPE voting><voting><vote>"+clients.key(var)+"</vote></voting>";
        SendToServerMsg(var,msg);
    }*/

}

void MyClient::waitAll()
{
    /* foreach (QTcpSocket* var, clients) {
        QString msg = "<!DOCTYPE changing><changing><wait/></changing>";
        SendToServerMsg(var,msg);
    }*/

}


void MyClient::slotDisplay(QString m)
{
    m_ptxtInfo->append(m);
}

void MyClient::slotDisconnected()
{
    clients.remove(clients.key((ClientSocket*)sender()));
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

void MyClient::slotn1(){

    /*map.insert("Ermon","Assistant");
    map.insert("Wendy","Doctor");
    map.insert("Helen","Gunmen");
    map.insert("Rick","Engineer");
    map.insert("Tau","Scientist");
    map.insert("Ygg","Signalmen");*/



    Qu->Send("<!DOCTYPE voting><voting><vote>Qu</vote></voting>");
    Ermon->Send("<!DOCTYPE voting><voting><vote>Qu</vote></voting>");
    Wendy->Send("<!DOCTYPE voting><voting><vote>Qu</vote></voting>");
    Helen->Send("<!DOCTYPE voting><voting><vote>Qu</vote></voting>");
    Rick->Send("<!DOCTYPE voting><voting><vote>Qu</vote></voting>");
    Tau->Send("<!DOCTYPE voting><voting><vote>Qu</vote></voting>");
    Ygg->Send("<!DOCTYPE voting><voting><vote>Qu</vote></voting>");
    QTimer::singleShot(500,this,SLOT(slotn2()));
    QTimer::singleShot(1000,this,SLOT(slotn3()));
    QTimer::singleShot(1500,this,SLOT(slotn4()));

}

void MyClient::slotn2(){
    Ermon->Send("<!DOCTYPE voting><voting><vote>Helen</vote></voting>");
    Wendy->Send("<!DOCTYPE voting><voting><vote>Helen</vote></voting>");
    Helen->Send("<!DOCTYPE voting><voting><vote>Helen</vote></voting>");
    Rick->Send("<!DOCTYPE voting><voting><vote>Helen</vote></voting>");
    Tau->Send("<!DOCTYPE voting><voting><vote>Helen</vote></voting>");
    Ygg->Send("<!DOCTYPE voting><voting><vote>Helen</vote></voting>");
}

void MyClient::slotn3(){
    Ermon->Send("<!DOCTYPE changing><changing><use item=\"Rotation\"><Ermon/><Wendy/><Rick/><Tau/><Ygg/></use></changing>");
}

void MyClient::slotn4(){
    Helen->Send("<!DOCTYPE changing><changing><use badge=\"Mop\">Rick</use></changing>");
    Helen->Send("<!DOCTYPE changing><changing><attack>Ermon</attack></changing>");
    Ermon->Send("<!DOCTYPE changing><changing><use badge=\"Mop\">Ermon</use></changing>");
    Ermon->Send("<!DOCTYPE changing><changing><wait/></changing>");
    Helen->Send("<!DOCTYPE changing><changing><infect>Ermon</attack></changing>");
    Wendy->Send("<!DOCTYPE changing><changing><wait/></changing>");
    Helen->Send("<!DOCTYPE changing><changing><wait/></changing>");
    Rick->Send("<!DOCTYPE changing><changing><wait/></changing>");
    Tau->Send("<!DOCTYPE changing><changing><wait/></changing>");
    Ygg->Send("<!DOCTYPE changing><changing><wait/></changing>");
}

void MyClient::slotn5(){
    m_pnameInput->setText("Ygg");
}

void MyClient::slotn6(){
    m_pnameInput->setText("Tau");
}

void MyClient::slotn7(){
    m_pnameInput->setText("Ugunday");
}

void MyClient::slotConnecting(){

    QStringList names;
    names <<"Qu" <<"Wendy"<<"Ermon"<<"Helen"<<"Ygg"<<"Tau"<<"Rick";

    foreach (QString na, names) {
        ClientSocket* n = new ClientSocket(na);
        connect(n,SIGNAL(displayMess(QString)),this,SLOT(slotDisplay(QString)));
        connect(n->_socket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
        clients.insert(na,n);
    }
    foreach (ClientSocket* var, clients.values()) {
        var->_socket->connectToHost("localhost", 21277);
    }
    Qu = clients.value("Qu");
    Ermon = clients.value("Ermon");
    Wendy = clients.value("Wendy");
    Helen = clients.value("Helen");
    Rick = clients.value("Rick");
    Tau = clients.value("Tau");
    Ygg = clients.value("Ygg");
}
