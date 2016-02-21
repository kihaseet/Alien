#ifndef PROTOBUF_MAKER_H
#define PROTOBUF_MAKER_H

#include <QObject>
#include "proto/types.pb.h"
#include "proto/server.pb.h"
#include "proto/client.pb.h"
#include "protocol.h"

class protobuf_maker: public Protocol
{
public:
    protobuf_maker();
public slots:
    void newAnalise(int _name, const QString input);

    void slotRegisterAnswer(int connectID, RegisterStatusType isCorrect);
    void slotRegisterUpdate(QList<player *> NameRolelist);
    void slotStartGame(QList<player*>playerlist);
    void slotTimeSwitch(int dayNo, TimeType type);
    void slotPlayerDisconnect(QString name);

    void slotVoting(VotingType type, QList<QString> list, ROLE targets);
    void slotEndVoting(ROLE targets,QString name,QString result);
    void slotChange(TurnObject turn);
    void slotSendMess(int ID, QString mess);

    void slotInventoryChange(int connectID, InvetoryChangeType type, ITEM item, int charge);
    void slotPlayerChange(int connectID, PlayerChangeType type, int value);
    void slotActionRequest(int connectID, RequestType type, QList<QString> targets);
    void slotActionResult(int connectID, ResultType type, TURN_TYPE action);
};

#endif // PROTOBUF_MAKER_H
