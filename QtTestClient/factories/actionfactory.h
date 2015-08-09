#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "types/action.h"
#include "types/player.h"

#include "types/currentplayer.h"

class ActionFactory
{
public:
    ActionFactory();
    static Action noAction();
    static Action useItem(Item item, QVector<ITarget> targets);
    static Action ultItem(Item item, QVector<ITarget> targets);
    static Action useBadge(Item item, QVector<ITarget> targets);
    static Action attack(Player player);
    static Action infect(Player player);
    static Action vote(Player player);
    static Action unvote();
    static Action sleep();
    static Action up();
    static Action down();
public:
    static CurrentPlayer* currentPlayer;
};

#endif // ACTIONFACTORY_H
