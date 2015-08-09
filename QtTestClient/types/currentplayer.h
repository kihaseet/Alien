#ifndef CURRENTPLAYER_H
#define CURRENTPLAYER_H

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
    bool yetVote;
    bool yetAttacked;
    QString lastAttacked;
    QString currentAttacked;
    bool yetInfect;
    bool yetUsed;
    bool yetWait;
    QVector<Action> didActions;
    QVector<Action> actions;
public:
    CurrentPlayer(QString name
                  , Status status
                  , QStringList roles
                  , PlayerImage image
                  , int hp = 3
                  , bool _isAlien = false);
//    void recalcActions();
    int getHP();
    void setHP(int hp);
    bool isAlien();
    bool isInfected();
    void setAlien(bool _isAlien);
    QVector<Action> getActions();
    void setActions(QVector<Action> actions);
    bool getYetAttack();
    bool getYetInfect();
    bool getYetUsed();
    bool getYetWait();
    bool getYetVote();
};

#endif // CURRENTPLAYER_H
