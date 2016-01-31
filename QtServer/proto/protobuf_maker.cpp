#include "protobuf_maker.h"

protobuf_maker::protobuf_maker()
{

}

void protobuf_maker::newAnalise(int _name, const QString input)
{
    ::Xenophobia::ClientMessage message;
    if(message.ParseFromString(input.toStdString())){
        switch (message.type()) {
        case ::Xenophobia::CMT_REGISTER_NAME:
            emit sigRegisterCreate(RegisterObject(_name,TT_REGNAME,QString::fromStdString(message.reg_name().name())));
            break;
        case ::Xenophobia::CMT_REGISTER_ROLE:
            emit sigRegisterCreate(RegisterObject(_name,TT_REGROLE,message.reg_role().role()));
            break;
        case ::Xenophobia::CMT_DISCONNECT:
            emit sigDisconnect(_name);
            break;
        case ::Xenophobia::CMT_DO_ACTION:
            TurnObject turn;
            turn.type
            emit sigTurnCreate(_name,TurnObject());
            break;
        default:
            break;
        }
    }

}

void protobuf_maker::slotSendVoteList(QList<VoteObject *> votelist)
{

}

void protobuf_maker::slotNameCorrect(int tempname, bool isCorrect)
{

}

void protobuf_maker::slotRoleCorrect(int _name, bool isCorrect)
{

}

void protobuf_maker::slotUpdateRoleList(QList<player *> NameRolelist)
{

}

void protobuf_maker::slotDisconnected(QList<player *> playerlist)
{

}

void protobuf_maker::slotStartGame(QList<player *> playerlist)
{

}

void protobuf_maker::slotStartPhase(int dayNo, bool isDay)
{

}

void protobuf_maker::slotStartVoting(ROLE targets, QList<QString> list)
{

}

void protobuf_maker::slotEndVoting(ROLE targets, QString name, QString result)
{

}

void protobuf_maker::slotSendMess(player *who, QString mess)
{

}

void protobuf_maker::slotSendTurn(TurnObject turn)
{

}

void protobuf_maker::slotSendStat(TurnObject turn)
{

}

