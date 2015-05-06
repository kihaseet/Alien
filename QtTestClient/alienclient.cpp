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

bool AlienClient::connect_(QString addr)
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
}

bool AlienClient::selectRole(QString name)
{
    protocol.sendSelectRole(name);
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

void AlienClient::errormess(QString mess)
{

}

void AlienClient::disconnect()
{

}

void AlienClient::onChange(onChangeInfo info)
{
    QString name = this->currentPlayer.name;
    this->currentPlayer = info.updated_stats;
    this->currentPlayer.name = name;
    emit updateActions(info.avaible_actions);
    emit updateEvents(info.events);
    emit updateStat(info.updated_stats);
}

void AlienClient::onSelect(onSelectInfo info)
{
    emit registerStatus(info.type);
    for (QString player : info.players)
    {
        players[player].role.clear();
        players[player].role.append(info.players[player]);
        players[player].name = player;
    }
    emit updatePlayers(players);
}

void AlienClient::onInit(onInitInfo info)
{
    switch (info.type)
    {
    case IT_DAYTIME:
    case IT_NIGHTTIME:
        emit updateInit(info.type);
        break;
    case IT_VOTING_FOR_ROLE:
    case IT_VOTING_FOR_ALIEN:
        emit startVoting(info.target, info.data);
        break;
    case IT_ENDVOTING_FOR_ROLE:
        emit endVoting(info.target, info.data[0], "");
        break;
    case IT_ENDVOTING_FOR_ALIEN:
        emit endVoting(info.target, info.data[0], info.data[1]);
        break;
    }
}

void AlienClient::onVote(onVoteInfo info)
{
    emit updateVoting(info.votelist);
}
