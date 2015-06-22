#include "alienclient.h"

AlienClient::AlienClient(QObject *parent) : QObject(parent)
{
    server_connection = new tcpclient();
    protocol.setConnection(server_connection);
    connect(server_connection, SIGNAL(GetData(QString)), &protocol, SLOT(GetData(QString)));
    connect(server_connection, SIGNAL(errormess(QString)), this, SLOT(errormess(QString)));
    connect(server_connection, SIGNAL(disconnect), this, SLOT(disconnect));

    connect(&protocol, SIGNAL(onChange(onChangeInfo)), this, SLOT(onChange(onChangeInfo)));
    connect(&protocol, SIGNAL(onInit(onInitInfo)), this, SLOT(onInit(onInitInfo)));
    connect(&protocol, SIGNAL(onSelect(onSelectInfo)), this, SLOT(onSelect(onSelectInfo)));
    connect(&protocol, SIGNAL(onVote(onVoteInfo)), this, SLOT(onVote(onVoteInfo)));
}

AlienClient::~AlienClient()
{

}

bool AlienClient::connect_(const QString addr)
{
    QStringList addr_port = addr.split(":");
    if (addr_port.count() != 2)
    {
        return false;
    }

    server_connection->connect_(addr_port[0], addr_port[1].toInt());
    return true;
}

bool AlienClient::register_(QString name)
{
    protocol.sendRegister(name);
    this->currentPlayer.name = name;
}

bool AlienClient::selectRole(QString name)
{
    protocol.sendSelectRole(name);
    this->currentPlayer.role.clear();
    this->currentPlayer.role.append(name);
}

void AlienClient::makeTurn(TurnObject& turn)
{
    if (turn.type == TT_VOTE || turn.type == TT_UNVOTE)
    {
        protocol.sendVote(turn.targets[0], turn.type == TT_UNVOTE);
    }
    else
    {
        protocol.sendAction(turn.type, turn.item, turn.targets);
    }
}

const CurrectPlayerInfo& AlienClient::getCurrentPlayer()
{
    return currentPlayer;
}

void AlienClient::errormess(QString mess)
{

}

void AlienClient::disconnect()
{

}

void AlienClient::onChange(onChangeInfo info)
{
//    QString name = this->currentPlayer.name;
//    this->currentPlayer = info.updated_stats;
//    this->currentPlayer.name = name;
    this->currentPlayer.update(info.updated_stats);
    qDebug() << "AlienClient: onChange: emit updateActions";
    emit updateActions(info.avaible_actions);
    qDebug() << "AlienClient: onChange: emit updateEvents";
    emit updateEvents(info.events);
    qDebug() << "AlienClient: onChange: emit updateStat";
    emit updateStat(info.updated_stats);
    if (info.players_info.size() != 0)
    {
        qDebug() << "AlienClient: onChange: emit updatePlayersInfo";
        emit updatePlayersInfo(info.players_info);
    }
}

void AlienClient::onSelect(onSelectInfo info)
{
    emit registerStatus(info.type);
    if(info.type==SRT_PLAYERLIST){
        qDebug() << "AlienClient: onSelect: emit updatePlayers";
        emit updatePlayers(info.players);
    }
}

void AlienClient::onInit(onInitInfo info)
{
    switch (info.type)
    {
    case IT_DAYTIME:
    case IT_NIGHTTIME:
        qDebug() << "AlienClient: emit updateInit";
        emit updateInit(info.type);
        break;
    case IT_VOTING_FOR_ROLE:
    case IT_VOTING_FOR_ALIEN:
        qDebug() << "AlienClient: emit startVoting";
        emit startVoting(info.target, info.data);
        break;
    case IT_ENDVOTING_FOR_ROLE:
        qDebug() << "AlienClient: emit endVoting";
        emit endVoting(info.target, info.data[0], "");
        break;
    case IT_ENDVOTING_FOR_ALIEN:
        qDebug() << "AlienClient: emit endVoting";
        emit endVoting(info.target, info.data[0], info.data[1]);
        break;
    }
}

void AlienClient::onVote(onVoteInfo info)
{
    qDebug() << "AlienClient: emit updateVoting";
    emit updateVoting(info.votelist);
}
