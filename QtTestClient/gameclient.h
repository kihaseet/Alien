#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QString>
#include <QVector>
#include <QObject>
#include "types/vote.h"
#include "types/player.h"
#include "types/action.h"
#include "protocol/xmlprotocol/xmlprotocol.h"
#include "factories/actionfactory.h"

typedef QVector<PlayerConstPtr> QConstPlayersVector;

class GameClient : public QObject
{
    Q_OBJECT

    bool Night;
    Vote* vote;
    QMap<PlayerPtr, int> voteTargets;
    CurrentPlayerPtr currentPlayer;
    QString address;
    QVector<PlayerPtr> players;
    QVector<PlayerPtr> onDutyPlayers;
    QVector<ItemType> ultedItems;
    XmlProtocol* protocol;
    int currentDay;

private:
    void recalcActions();
    PlayerPtr getPlayer(QString name);

    void brute_copy(QVector<PlayerPtr>& from, QConstPlayersVector& to);
public:
    GameClient();
    Vote* getCurrentVoting();
    QConstPlayersVector getPlayers();
    const PlayerPtr getPlayerByName(QString name);
    QConstPlayersVector getVoteTargets();
    QConstPlayersVector getOnDutyPlayers();
    CurrentPlayerPtr getCurrentPlayer();
    QVector<ItemType> getWreckedItems();
    int getCurrentDay();
    bool connectToServer(QString address);
    bool registerName(QString name);
    bool registerRole(QString role);
    bool doAction(Action action);
    void disconnectFromServer();
    bool reconnect();

signals:
    void connected();
    void registerNameStatus(bool isCorrect);
    void registerRoleStatus(bool isCorrect);
    void dayUpdate(int day, bool isDay);
    void startVoting(Vote& vote);
    void endVoting();
    void updateActions(QVector<ActionType> actions);
    void updateItems(QVector<Item> items);
    void updatePlayers(QConstPlayersVector players);
    void log(QString text);
    void errorLog(QString text);
    void voteUpdate(QString playerName, int votes);

private slots:
    void nameCorrect();
    void nameIncorrect();
    void roleCorrect();
    void roleIncorrect();
    void dayTime(int day);
    void nightTime();
    void startVote(Vote vote);
    void endVote(EndVote endvote);
    void playerUlted(ItemType item);
    void playersUpdate(QVector<Player> players);
    void statUpdate(const IStatUpdate& stat);
    void sig_event(const IEvent& e);
    void errorMessage(QString message);
    void disconnected();
    void sig_connected();
};

#endif // GAMECLIENT_H
