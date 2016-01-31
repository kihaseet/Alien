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
        case Xenophobia::CMT_DO_ACTION:
            emit sigTurnCreate(_name,TurnObject(message.do_action()));
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
    ::Xenophobia::ServerMessage message;
    ::Xenophobia::RegisterAnswer answer;
    if(isCorrect)
        answer.set_status(Xenophobia::NAME_CORRECT);
    else
        answer.set_status(Xenophobia::NAME_INCORRECT);

    message.set_type(::Xenophobia::SMT_REGISTER_ANSWER);
    message.set_allocated_register_answer(&answer);

    emit sigSendToClient(tempname,QString::fromStdString(message.SerializeAsString()));
}

void protobuf_maker::slotRoleCorrect(int _name, bool isCorrect)
{
    ::Xenophobia::ServerMessage message;
    ::Xenophobia::RegisterAnswer answer;
    if(isCorrect)
        answer.set_status(Xenophobia::ROLE_CORRECT);
    else
        answer.set_status(Xenophobia::ROLE_INCORRECT);

    message.set_type(::Xenophobia::SMT_REGISTER_ANSWER);
    message.set_allocated_register_answer(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToClient(_name,out);
}

void protobuf_maker::slotUpdateRoleList(QList<player *> NameRolelist)
{
    ::Xenophobia::ServerMessage message;
    ::Xenophobia::RegisterUpdate answer;
    ::google::protobuf::Map< ::std::string, ::types::Role >* t = answer.mutable_players();
    foreach (player* man, NameRolelist) {
        if(!man->rolelist.isEmpty())
            t->insert(google::protobuf::MapPair<std::string, types::Role>(man->name.toStdString(),(types::Role)man->rolelist.first()));
        else
            t->insert(google::protobuf::MapPair<std::string, types::Role>(man->name.toStdString(),types::PASSENGER));
    }

    message.set_type(Xenophobia::SMT_REGISTER_UPDATE);
    message.set_allocated_register_update(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToAll(out);
}

void protobuf_maker::slotDisconnected(QList<player *> playerlist)
{

}

void protobuf_maker::slotStartGame(QList<player *> playerlist)
{
    ::Xenophobia::ServerMessage message;
    ::Xenophobia::StartGame answer;

    foreach (player* man, playerlist) {
        Xenophobia::PlayerInfo* t = answer.add_players();
        t->set_name(man->name.toStdString());
        if(!man->rolelist.isEmpty())
            foreach (ROLE rol, man->rolelist) {
                t->add_roles((types::Role)rol);
            }
        else
            t->add_roles(types::PASSENGER);
        t->set_onduty(man->ImDuty);
        t->set_online(man->online);
        if(man->status==0)
            t->set_status(types::PS_DOWN);
        else
            t->set_status(types::PS_UP);
        t->set_avatar(1);
    }

    message.set_type(Xenophobia::SMT_START_GAME);
    message.set_allocated_start_game(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToAll(out);
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

