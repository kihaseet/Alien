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

class GameClient : public QObject
{
    Q_OBJECT

    bool Night;
    Vote* vote;
    QMap<Player, int> voteTargets;
    ITarget lastVote;
    CurrentPlayer* currentPlayer;
    QString address;
    QVector<Player> players;
    QVector<Player> onDutyPlayers;
    QVector<ItemType> ultedItems;
    IProtocol* protocol;
    int currentDay;

private:
    void recalcActions();
    Player* getPlayer(QString name);
public:
    GameClient();
    Vote* getCurrentVoting();
    QVector<Player> getPlayers();
    QVector<Player> getVoteTargets();
    QVector<Player> getOnDutyPlayers();
    int getCurrentDay();
    bool connect(QString address);
    bool registerName(QString name);
    bool registerRole(QString role);
    bool doAction(Action action);
    void disconnect();
    bool reconnect();

signals:
    void registerNameStatus(bool isCorrect);
    void registerRoleStatus(bool isCorrect);
    void dayUpdate(int day, bool isDay);
    void startVoting(const Vote& vote);
    void endVoting();
    void updateActions(QVector<Action> actions);
    void updateItems(QVector<Item> items);
    void updatePlayers(QVector<Player> players);
    void log(QString text);
    void errorLog(QString text);

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
    void statUpdate(IStatUpdate stat);
    void event(IEvent event);
    void errorMessage(QString message);
    void disconnected();
};

#endif // GAMECLIENT_H
