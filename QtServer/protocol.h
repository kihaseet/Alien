#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <QObject>
#include "player.h"
#include "event.h"

class Protocol:public QObject
{
    Q_OBJECT
public:
    Protocol(){}
public slots:
    virtual void newAnalise(int _name, const QString input) = 0;

    virtual void slotSendVoteList(QList<VoteObject *> votelist) = 0;
    virtual void slotNameCorrect(int tempname, bool isCorrect) = 0;
    virtual void slotRoleCorrect(int _name, bool isCorrect) = 0;
    virtual void slotUpdateRoleList(QList<player*> NameRolelist) = 0;
    virtual void slotDisconnected(QList<player*>playerlist) = 0;

    virtual void slotStartGame(QList<player*>playerlist) = 0;
    virtual void slotStartPhase(int dayNo, bool isDay) = 0;
    virtual void slotStartVoting(ROLE targets,QList<QString>list) = 0;
    virtual void slotEndVoting(ROLE targets,QString name,QString result) = 0;

    virtual void slotSendMess(player *who, QString mess) = 0;
    virtual void slotSendTurn(TurnObject turn) = 0;
    virtual void slotSendStat(TurnObject turn) = 0;
signals:
    void sigTurnCreate(int who,TurnObject turn);
    void sigRegisterCreate(RegisterObject regObj);
    void sigDisconnect(int who);
    void sigSendToClient(int _name,QString _xmldoc);
    void sigSendToAll(QString _xmldoc);
};

#endif // PROTOCOL_H
