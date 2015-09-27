#include "factories/actionfactory.h"

CurrentPlayerPtr ActionFactory::currentPlayer = nullptr;

ActionFactory::ActionFactory()
{

}

Action ActionFactory::noAction()
{
    return Action(ActionType::TT_NO_ACTION, ITarget(), QVector<ITarget>());
}

Action ActionFactory::useItem(Item item, QVector<ITarget> targets)
{
    return Action(ActionType::TT_USE_ITEM, *currentPlayer, targets, item);
}

Action ActionFactory::ultItem(Item item, QVector<ITarget> targets)
{
    return Action(ActionType::TT_ULT_ITEM, *currentPlayer, targets, item);
}

Action ActionFactory::useBadge(Item item, QVector<ITarget> targets)
{
    return Action(ActionType::TT_BADGE, *currentPlayer, targets, item);
}

Action ActionFactory::attack(Player player)
{
    QVector<ITarget> targets;
    targets.push_back(player);
    return Action(ActionType::TT_ATTACK, *currentPlayer, targets);
}

Action ActionFactory::infect(Player player)
{
    QVector<ITarget> targets;
    targets.push_back(player);
    return Action(ActionType::TT_INFECT, *currentPlayer, targets);
}

Action ActionFactory::vote(PlayerConstPtr player)
{
    QVector<ITarget> targets;
    targets.push_back(*player);
    return Action(ActionType::TT_VOTE, *currentPlayer, targets);
}

Action ActionFactory::unvote()
{
    return Action(ActionType::TT_UNVOTE, *currentPlayer, QVector<ITarget>());
}

Action ActionFactory::sleep()
{
    return Action(ActionType::TT_SKIP, *currentPlayer, QVector<ITarget>());
}

Action ActionFactory::up()
{
    return Action(ActionType::TT_UP, *currentPlayer, QVector<ITarget>());
}

Action ActionFactory::down()
{
    return Action(ActionType::TT_DOWN, *currentPlayer, QVector<ITarget>());
}

