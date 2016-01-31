#ifndef PROTOBUF_MAKER_H
#define PROTOBUF_MAKER_H

#include <QObject>
#include "proto/types.pb.h"
#include "proto/server.pb.h"
#include "protocol.h"

class protobuf_maker: public Protocol
{
public:
    protobuf_maker();
public slots:
    void newAnalise(int _name, const QString input);

    void slotSendVoteList(QList<VoteObject *> votelist);
    void slotNameCorrect(int tempname, bool isCorrect);
    void slotRoleCorrect(int _name, bool isCorrect);
    void slotUpdateRoleList(QList<player*> NameRolelist);
    void slotDisconnected(QList<player*>playerlist);

    void slotStartGame(QList<player*>playerlist);
    void slotStartPhase(int dayNo, bool isDay);
    void slotStartVoting(ROLE targets,QList<QString>list);
    void slotEndVoting(ROLE targets,QString name,QString result);

    void slotSendMess(player *who, QString mess);
    void slotSendTurn(TurnObject turn);
    void slotSendStat(TurnObject turn);

};

#endif // PROTOBUF_MAKER_H
