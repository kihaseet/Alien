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

    //QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    ClientSocket* pClientSocket = new ClientSocket(m_ptcpServer->nextPendingConnection(),"");
    m_clients.push_back(pClientSocket);

    connect(pClientSocket->_socket, SIGNAL(disconnected()),
            this, SLOT(on_disconnected()));
    connect(pClientSocket->_socket, SIGNAL(readyRead()),
            this, SLOT(slotReadClient()));
    add_to_log("[Server] ","New connection");
}

void Server::on_disconnected(){
    add_to_log("[Server] ","client disconnected");

    QTcpSocket* client = (QTcpSocket*)sender();
    foreach (ClientSocket* cl, m_clients) {
        if(cl->_socket==client){
            m_clients.removeOne(cl);
            client->deleteLater();
        }
    }
}

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_5);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QString str;
        in >> str;

        //add_to_log("[Server] ",str);
        foreach (ClientSocket* client, m_clients) {
            if (client->_socket==pClientSocket){
                if (client->_name==""){
                    client->_name=str;
                    //add_to_log(str,str);
                    //add_to_log("[Server] ","new message!");
                    send_to_analise(str,str);
                } else{
                    //add_to_log(client->_name,str);
                    add_to_log(client->_name,"new message!");
                    send_to_analise(client->_name,str);
                }
            }
        }

        m_nNextBlockSize = 0;
        //break;
    }
}



void Server::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    qDebug() << "[Server]"<<str;
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    pSocket->write(arrBlock);
}

void Server::verifyClientName(QString tempname,QString name){
    foreach (ClientSocket* client, m_clients)
    {
        if(client->_name==tempname)client->_name=name;
    }
}

void Server::noVerifyClientName(QString name){
    foreach (ClientSocket* client, m_clients)
    {
        if(client->_name==name){
            client->_socket->close();
            m_clients.removeOne(client);
            break;
        }

    }
}


void Server::slotsendToClient(QString _name,QString msg)
{
    foreach (ClientSocket* client, m_clients) {
        if (client->_name==_name)sendToClient(client->_socket,msg);
    }
}

void Server::add_to_log(QString _name,QString msg){
    emit addLogToGui(_name,msg);


}

void Server::send_to_analise(QString _name,QString msg){
    emit sendToAnalise(_name,msg);
    slotsendToClient(_name,msg);
}
