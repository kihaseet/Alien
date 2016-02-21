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
    virtual void slotRegisterAnswer(int connectID, RegisterStatusType isCorrect) = 0;
    virtual void slotRegisterUpdate(QList<player*> NameRolelist) = 0;
    virtual void slotStartGame(QList<player*>playerlist) = 0;
    virtual void slotTimeSwitch(int dayNo, TimeType type) = 0;
    virtual void slotVoting(VotingType type ,QList<QString>list, ROLE targets)=0;
    virtual void slotEndVoting(ROLE targets,QString name,QString result) = 0;
    virtual void slotChange(TurnObject turn) = 0;         //изменения с другими игроками
    virtual void slotInventoryChange(int connectID,InvetoryChangeType type, ITEM item, int charge) = 0; //изменения в инвентаре
    virtual void slotPlayerChange(int connectID, PlayerChangeType type, int value) = 0;    //изменение с хп, заражением или статусом(?)
    virtual void slotActionRequest(int connectID, RequestType type, QList<QString> targets) = 0;   //посылается при хардрезолве и нидротации
    virtual void slotActionResult(int connectID, ResultType type, TURN_TYPE action) = 0;           //подтверждение действия или предмета
    virtual void slotPlayerDisconnect(QString name) = 0;
    virtual void slotSendMess(int ID,QString mess) = 0;
signals:
    void sigTurnCreate(const int who,TurnObject turn);
    void sigRegisterCreate(RegisterObject regObj);
    void sigDisconnect(int who);
    void sigSendToClient(const int name,const QString &doc);
    void sigSendToAll(const QString &doc);
};

#endif // PROTOCOL_H
