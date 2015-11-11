#ifndef CURRENTPLAYER_H
#define CURRENTPLAYER_H

#include <memory>

#include <QString>
#include <QVector>
#include "player.h"
#include "item.h"
#include "action.h"

class CurrentPlayer : public Player
{
private:
    int hp;
    bool _isAlien;
    bool _isInfected;
//    QString lastAttacked;
//    QString currentAttacked;
    QVector<Action> didActions;
    QVector<ActionType> actions;
    QVector<Item> items;
public:
    CurrentPlayer(QString name
                  , Status status
                  , QStringList roles
                  , PlayerImage image
                  , int hp = 3
                  , bool _isAlien = false);
    int getHP();
    void setHP(int hp);
    bool isAlien();
    bool isInfected();
    void setAlien(bool _isAlien);

    QVector<ActionType> getActions();
    void setActions(QVector<ActionType> actions);

    QVector<Item> getItems();
    void setItems(QVector<Item> items);

    void addDidAction(Action action);
    bool didPlayerAction(Action action);
    bool didPlayerAction(ActionType action);
};

typedef std::shared_ptr<CurrentPlayer> CurrentPlayerPtr;

#endif // CURRENTPLAYER_H
