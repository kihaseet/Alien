#ifndef _Server_h_
#define _Server_h_

#include <QWidget>
#include "clientsocket.h"

class QTcpServer;
class QTextEdit;
class QTcpSocket;

// ======================================================================
class Server : public QObject {
Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    quint16 m_nNextBlockSize;

private:
    QList<ClientSocket*> m_clients;


public:
    Server(int nPort);
    void add_to_log(QString _name, QString msg);



signals:
    void addLogToGui(QString n, QString s);
    void sendToAnalise(int n, QString msg);
    void client_disconnected(int n);
    void client_connected();

public slots:
            void slotNewConnection();
            void slotReadClient ();
            void on_disconnected();
            void slotsendToClient(int _name, QString msg);
            void noVerifyClientName(int name);
            void send2all(QString msg);
};
#endif //_MyServer_h_
