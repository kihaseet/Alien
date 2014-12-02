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
    QWidget *_widget;
    quint16 m_nNextBlockSize;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);
    QList<ClientSocket*> m_clients;


public:
    Server(int nPort, QWidget* pwgt);
    void add_to_log(QString _name, QString msg);
    void send_to_analise(QString _name,QString msg);


signals:
    void addLogToGui(QString n, QString s);
    void sendToAnalise(QString n, QString msg);
    void client_disconnected(QString n);

public slots:
    virtual void slotNewConnection();
            void slotReadClient ();
            void on_disconnected();
            void slotsendToClient(QString _name, QString msg);
            void verifyClientName(QString tempname,QString name);
            void noVerifyClientName(QString name);
};
#endif //_MyServer_h_
