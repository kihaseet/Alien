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


void protobuf_maker::slotStartGame(QList<player *> playerlist)
{
    Xenophobia::ServerMessage message;
    Xenophobia::StartGame answer;

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

void protobuf_maker::slotEndVoting(ROLE targets, QString name, QString result)
{
    Xenophobia::ServerMessage message;
    Xenophobia::EndVoting answer;

    if(targets == RT_ALIEN)
        answer.set_type(types::FOR_ALIEN);
    else
        answer.set_type(static_cast<types::VotingType>(targets));

    if(name!=""){
        types::ITarget tar;
        tar.set_type(types::TAT_NAME);
        tar.set_name(name.toStdString());
        answer.set_allocated_target(&tar);
    }

    if(result!=""){
        answer.set_result(result.toStdString());
    }

    message.set_type(Xenophobia::SMT_END_VOTING);
    message.set_allocated_end_voting(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToAll(out);

}



void protobuf_maker::slotRegisterAnswer(int connectID, RegisterStatusType isCorrect)
{
    Xenophobia::ServerMessage message;
    Xenophobia::RegisterAnswer answer;
    answer.set_status((Xenophobia::RegisterStatusType)isCorrect);

    message.set_type(Xenophobia::SMT_REGISTER_ANSWER);
    message.set_allocated_register_answer(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToClient(connectID,out);
}

void protobuf_maker::slotRegisterUpdate(QList<player *> NameRolelist)
{
    Xenophobia::ServerMessage message;
    Xenophobia::RegisterUpdate answer;
    //::google::protobuf::Map< ::std::string, ::types::Role >* t = answer.mutable_players();
    auto *t = answer.mutable_players();
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

void protobuf_maker::slotTimeSwitch(int dayNo, TimeType type)
{
    Xenophobia::ServerMessage message;
    Xenophobia::TimeSwitch answer;

    answer.set_day_number(dayNo);
    answer.set_time((Xenophobia::TimeType)type);

    message.set_type(Xenophobia::SMT_TIME_SWITCH);
    message.set_allocated_time_switch(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToAll(out);
}

void protobuf_maker::slotPlayerDisconnect(QString name)
{
    Xenophobia::ServerMessage message;
    Xenophobia::Change answer;

    auto *event = answer.mutable_event();
    types::ITarget event_who;

    event_who.set_type(types::TAT_NAME);
    event_who.set_name(name.toStdString());

    event->set_event(types::ET_DISCONNECT);
    event->set_allocated_event_who(&event_who);

    message.set_type(Xenophobia::SMT_CHANGE);
    message.set_allocated_change(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToAll(out);
}


void protobuf_maker::slotVoting(VotingType type, QList<QString> list, ROLE targets)
{
    Xenophobia::ServerMessage message;
    Xenophobia::Voting answer;

    if(type == FOR_ROLE) {
        answer.set_type(static_cast<types::VotingType>(targets));
        //TODO после изменения карты в список игроков здесь будет список с именами
    }
    else
        answer.set_type(types::FOR_ALIEN);

    foreach (QString name, list) {
        auto *t = answer.add_targets();
        t->set_type(types::TAT_NAME);
        t->set_name(name.toStdString());
    }

    message.set_type(Xenophobia::SMT_VOTING);
    message.set_allocated_voting(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToAll(out);
}


void protobuf_maker::slotInventoryChange(int connectID, InvetoryChangeType type, ITEM item, int charge)
{
    Xenophobia::ServerMessage message;
    Xenophobia::InvetoryChange answer;

    answer.set_type((Xenophobia::InvetoryChangeType)type);
    answer.set_item((types::Item)item);
    answer.set_charge(charge);

    message.set_type(Xenophobia::SMT_INVENTORY_CHANGE);
    message.set_allocated_inventory_change(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToClient(connectID, out);
}

void protobuf_maker::slotChange(TurnObject turn)
{
    Xenophobia::ServerMessage message;
    Xenophobia::Change answer;

    auto *event = answer.mutable_event();
    types::ITarget event_who;
    types::ITarget event_object;
    types::ITarget* event_target;

    if (turn.type == TT_USE_ITEM
            || turn.type == TT_ULT_ITEM
            || turn.type == TT_USE_BADGE){
        event->set_event(static_cast<types::EventType>(turn.type));
        event_object.set_type(types::TAT_ITEM);
        event_object.set_item(static_cast<types::Item>(turn.item));
        if(turn.item == IT_BATTERY){
            event_target = event->add_event_target();
            event_target->set_type(types::TAT_ITEM);
            event_target->set_item((types::Item)TurnObject::ItemDescr.value(turn.targets.first()));
        }
        else {
            while(!turn.targets.isEmpty()){
                event_target = event->add_event_target();
                event_target->set_type(types::TAT_NAME);
                event_target->set_name(turn.targets.dequeue().toStdString());      //TODO после изменения протокола делать мультитаргетовое присваивание
            }
        }
        event->set_allocated_event_object(&event_object);
    }
    else{
        switch(turn.type){
        case TT_GETROLE:
            event->set_event(types::ET_GET_ROLE);
            break;
        case TT_DELROLE:
            event->set_event(types::ET_DEL_ROLE);
            break;
        case TT_CONNECT:
            event->set_event(types::ET_CONNECT);
            break;
        case TT_DUTY:
            event->set_event(types::ET_GET_DUTY);
            break;
        case TT_DIED:
            event->set_event(types::ET_DIED);
            break;
        case TT_DOWN:
            event->set_event(types::ET_DOWN);
            break;
        case TT_UP:
            event->set_event(types::ET_UP);
            break;
        case TT_VOTE:
            event->set_event(types::ET_VOTE);
            break;
        case TT_UNVOTE:
            event->set_event(types::ET_UNVOTE);
            break;
        }
    }
    while(!turn.targets.isEmpty()){
        event_target = event->add_event_target();
        event_target->set_type(types::TAT_NAME);
        event_target->set_name(turn.targets.dequeue().toStdString());      //TODO после изменения протокола делать мультитаргетовое присваивание
    }

    event_who.set_type(types::TAT_NAME);
    event_who.set_name(turn.wh->name.toStdString());
    event->set_allocated_event_who(&event_who);

    message.set_type(Xenophobia::SMT_CHANGE);
    message.set_allocated_change(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToAll(out);
}

void protobuf_maker::slotSendMess(int ID, QString mess)
{
    Xenophobia::ServerMessage message;
    Xenophobia::Change answer;

    auto *event = answer.mutable_event();
    event->set_event(types::ET_INGAME_MESSAGE);
    event->set_payload(mess.toStdString());


    message.set_type(Xenophobia::SMT_CHANGE);
    message.set_allocated_change(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToClient(ID, out);
}


void protobuf_maker::slotPlayerChange(int connectID, PlayerChangeType type, int value)
{
    Xenophobia::ServerMessage message;
    Xenophobia::PlayerChange answer;

    answer.set_type((Xenophobia::PlayerChangeType)type);
    answer.set_value(value);

    message.set_type(Xenophobia::SMT_PLAYER_CHANGE);
    message.set_allocated_player_change(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToClient(connectID, out);
}

void protobuf_maker::slotActionRequest(int connectID, RequestType type, QList<QString> targets)
{
    Xenophobia::ServerMessage message;
    Xenophobia::ActionRequest answer;

    answer.set_type((Xenophobia::RequestType)type);
    foreach (QString name, targets) {
        auto *target = answer.add_targets();
        target->set_type(types::TAT_NAME);
        target->set_name(name.toStdString());
    }

    message.set_type(Xenophobia::SMT_ACTION_REQUEST);
    message.set_allocated_action_request(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToClient(connectID, out);
}

void protobuf_maker::slotActionResult(int connectID, ResultType type, TURN_TYPE action)
{
    Xenophobia::ServerMessage message;
    Xenophobia::ActionResult answer;

    answer.set_type((Xenophobia::ResultType)type);
    answer.set_action((types::Action)action);

    message.set_type(Xenophobia::SMT_ACTION_RESULT);
    message.set_allocated_action_result(&answer);

    QString out = QString::fromStdString(message.SerializeAsString());
    emit sigSendToClient(connectID, out);
}
