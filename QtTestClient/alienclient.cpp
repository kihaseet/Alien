#include "alienclient.h"

AlienClient::AlienClient(QObject *parent) : QObject(parent)
{
    server_connection = new tcpclient();
    protocol.setConnection(server_connection);
    connect(server_connection, SIGNAL(GetData(QString)), &protocol, SLOT(GetData(QString)));

    connect(&protocol
            , SIGNAL(GetParsedData(SERVER_RESPONSE_TYPE,QMap<QString,AlienClient::PlayerInfo>&))
            , this
            , SLOT(GetParsedData(SERVER_RESPONSE_TYPE,QMap<QString,AlienClient::PlayerInfo>&)));

    connect(server_connection, SIGNAL(errormess(QString)), this, SLOT(errormess(QString)));
    connect(server_connection, SIGNAL(disconnect), this, SLOT(disconnect));
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
