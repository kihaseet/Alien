#include <QTime>
#include <QtNetwork>
#include "server.h"
#include <QtGui>


Server::Server(int nPort, QWidget* pwgt /*=0*/) : m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);
    _widget=pwgt;
    
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort))
    {
        add_to_log("[Server] ","Server Error "+ m_ptcpServer->errorString());
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
}

/*virtual*/ void Server::slotNewConnection()
{
    
    QTcpSocket* pSock = m_ptcpServer->nextPendingConnection();
    ClientSocket* pClientSocket = new ClientSocket(pSock,pSock->socketDescriptor());
    m_clients.push_back(pClientSocket);
    connect(pClientSocket->_socket, SIGNAL(disconnected()),
            this, SLOT(on_disconnected()));
    connect(pClientSocket->_socket, SIGNAL(readyRead()),
            this, SLOT(slotReadClient()));
    add_to_log("[Server] ","New connection");
    emit client_connected();
}

void Server::on_disconnected(){
    QTcpSocket* client = (QTcpSocket*)sender();
    foreach (ClientSocket* cl, m_clients) {
        if(cl->_socket==client){
            add_to_log(QString::number(cl->_name),"client disconnected");
            emit client_disconnected(cl->_name);
            m_clients.removeOne(cl);
            client->deleteLater();
        }
    }
}
void Server::send2all(QString msg){
    foreach (ClientSocket* client, m_clients) {
        QString tmp = msg+'\n';
        QByteArray arrBlock = tmp.toLocal8Bit();
        client->_socket->write(arrBlock);
    }
}

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    
    QString str;
    if(pClientSocket->canReadLine()){
        QByteArray data = pClientSocket->readAll();
        str = data.data();
        str=str.trimmed();

        foreach (ClientSocket* client, m_clients) {
            if (client->_socket==pClientSocket){
                emit sendToAnalise(client->_name,str);
            }
        }
    }
}

void Server::noVerifyClientName(int name){
    foreach (ClientSocket* client, m_clients)
    {
        if(client->_name==name){
            client->_socket->close();
            m_clients.removeOne(client);
            break;
        }
        
    }
}


void Server::slotsendToClient(int _name,QString msg)
{
    foreach (ClientSocket* client, m_clients) {
        if (client->_name==_name){
            QString tmp = msg+'\n';
            QByteArray arrBlock = tmp.toLocal8Bit();
            client->_socket->write(arrBlock);
        }
    }
}

void Server::add_to_log(QString _name,QString msg){
    emit addLogToGui(_name,msg);
    
}
