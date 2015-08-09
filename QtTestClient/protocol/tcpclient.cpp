#include "tcpclient.h"


tcpclient::tcpclient()
{
    serv = new QTcpSocket();
    connect(serv, SIGNAL(connected()),this, SLOT(slotConnected()));
    connect(serv, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(slotError(QAbstractSocket::SocketError)));

    connect(serv,SIGNAL(readyRead()),SLOT(readData()));
    buffer = "";
    BytesReaded = 0;
    BytesToRead = 0;
}

void tcpclient::sendData(QString document)
{
    QString tmp = document +'\n';
    QByteArray data = tmp.toLocal8Bit();
    serv->write(data);
}

QString tcpclient::processData(QString str)
{
    int currentSize = str.length();
    if (BytesToRead == 0)
    {
        QString dataSizeStr = str.mid(0, str.indexOf("<!"));
        int dataSize = dataSizeStr.toInt() - 1;
        currentSize -= dataSizeStr.length();
        str = str.mid(dataSizeStr.length());

        if (dataSize > currentSize)
        {
            buffer += str;
            BytesReaded = currentSize;
            BytesToRead = dataSize;
        }
        else if (dataSize == currentSize)
        {
            emit GetData(str + "\n");
        }
        else
        {
            buffer = str.mid(0, dataSize);
            GetData(buffer);
            buffer = "";
            return str.mid(dataSize);
        }
    }
    else
    {
        if (BytesToRead - BytesReaded > currentSize)
        {
            buffer += str;
            BytesReaded += currentSize;
        }
        else if (BytesToRead - BytesReaded < currentSize)
        {
            buffer += str.mid(0, BytesToRead - BytesReaded);
            str = str.mid(BytesToRead - BytesReaded);
            emit GetData(buffer + "\n");
            buffer = "";
            BytesReaded = 0;
            BytesToRead = 0;
            return str;
        }
        else
        {
            buffer += str;
            emit GetData(buffer + "\n");
            buffer = "";
            BytesReaded = 0;
            BytesToRead = 0;
            return "";
        }
    }

    return "";
}

void tcpclient::readData()
{
    QTcpSocket* socket = ((QTcpSocket*)sender());
    if(socket->canReadLine()){
        QByteArray data = socket->readAll();
        QString tmp = data.data();
        tmp=tmp.trimmed();//полученное сообщение
        qDebug() << "********************************NEW TCP DATA***********************************************";
        qDebug() << "**************************TCP DATA*************************"
                 << tmp
                 << endl
                 << "**************************TCP DATA END*********************";

        QString strToProcess = tmp;

        while((strToProcess = processData(strToProcess)).length() != 0)
        {
            qDebug() << "******************** TCP CONTINUE PROCESS DATA ************************"
                     << strToProcess
                     << endl
                     << "******************** TCP CONTINUE PROCESS DATA END ********************";
        }

        qDebug() << "******************************END TCP DATA**************************************************";
    }
}

void tcpclient::slotError(QAbstractSocket::SocketError err)
{
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host was not found." :
           err == QAbstractSocket::RemoteHostClosedError ? "The remote host is closed." :
           err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused." :
                                                            QString(serv->errorString()) );
    emit errormess(strError);
}

void tcpclient::slotConnected()
{
    connect(serv,SIGNAL(disconnected()),this,SLOT(slotDisconect()));
    emit errormess("Loading player's list...");
}

void tcpclient::connect_(QString addr, int Port){
    this->nPort = Port;
    serv->connectToHost(addr,Port);
}

void tcpclient::slotDisconect(){
    emit sig_disconnect();
    disconnect(serv,SIGNAL(disconnected()),this,SLOT(slotDisconect()));
}
