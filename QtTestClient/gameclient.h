#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QString>
#include <QVector>
#include "types/vote.h"
#include "types/player.h"
#include "types/action.h"
#include "protocol/xmlprotocol/xmlprotocol.h"

class GameClient
{
    bool Night;
    Vote* vote;
    QMap<Player, int> targets;
    Player* lastVote;
    CurrentPlayer* currentPlayer;
    QString address;
    QVector<Player> players;
    QVector<Player> onDutyPlayers;
    IProtocol* protocol;
    int currentDay;
public:
    GameClient();
    bool isNight();
    Vote* getCurrentVoting();
    QVector<Player> getPlayers();
    QVector<Player> voteTargets();
    QVector<Player> getOnDutyPlayers();
    int getCurrentDay();
    bool connect(QString address);
    bool registerName(QString name);
    bool registerRole(QString role);
    bool doAction(Action action);
    void disconnect();
    bool reconnect();
};

#endif // GAMECLIENT_H
