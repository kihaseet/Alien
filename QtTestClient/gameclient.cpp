#include "gameclient.h"

GameClient::GameClient()
{
    this->lastVote = nullptr;
    this->Night = false;
    this->onDutyPlayers.clear();
    this->players.clear();
    this->protocol  = new XmlProtocol();
    this->targets.clear();
    this->vote = nullptr;
}

bool GameClient::isNight()
{
    return this->Night;
}

Vote *GameClient::getCurrentVoting()
{
    return this->vote;
}

QVector<Player> GameClient::getPlayers()
{
    return this->players;
}

QVector<Player> GameClient::voteTargets()
{
    QVector<Player> ret_players;
    for (QString player_name: vote->getTargets())
    {
        for (Player& player: this->players)
        {
            if (player.getName() == player_name)
            {
                ret_players.push_back(player);
                break;
            }
        }
    }

    return ret_players;
}

QVector<Player> GameClient::getOnDutyPlayers()
{
    return this->onDutyPlayers;
}

bool GameClient::connect(QString address)
{
    return protocol->_connect(address);
}

bool GameClient::registerName(QString name)
{
    return protocol->registerName(name);
}

bool GameClient::registerRole(QString role)
{
    return protocol->registerRole(role);
}

bool GameClient::doAction(Action action)
{
    protocol->doAction(action);
    return true;
}

void GameClient::disconnect()
{
    protocol->_disconnect();
}

bool GameClient::reconnect()
{
    protocol->reconnect(this->address);
    return true;
}

