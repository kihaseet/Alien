#ifndef IPROTOCOL_H
#define IPROTOCOL_H

#include <QString>
#include <QVector>
#include <QObject>
#include "types/action.h"
#include "types/vote.h"
#include "types/endvote.h"
#include "types/player.h"
#include "statupdate/istatupdate.h"
#include "events/ievent.h"
#include "tcpclient.h"

class IProtocol: public QObject
{
    Q_OBJECT
protected:
    tcpclient tcpClient;
public:
    IProtocol();
    virtual bool _connect(QString& address) = 0;
    virtual bool registerName(QString& name) = 0;
    virtual bool registerRole(QString& role) = 0;
    virtual void doAction(Action& action) = 0;
    virtual void _disconnect() = 0;
    virtual void reconnect(QString& address) = 0;

signals:
    void nameCorrect();
    void nameIncorrect();
    void roleCorrect();
    void roleIncorrect();
    void dayTime(int day);
    void nightTime();
    void startVote(Vote vote);
    void endVote(EndVote endvote);
    void playerUlted(ItemType item);
    void playersUpdate(QVector<Player> players);
    void statUpdate(IStatUpdate stat);
    void event(const IEvent& event);
    void errorMessage(QString message);
    void disconnected();
    void connected();

//public slots:
//    virtual void GetData(QString msg) = 0;
//    virtual void errormess(QString mess) = 0;
//    virtual void sig_disconnect() = 0;
//    virtual void sig_connected() = 0;
};

#endif // IPROTOCOL_H
