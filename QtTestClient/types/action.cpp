#include "types/action.h"

Action::Action()
{

}

Action::Action(ActionType actionType, ITarget user, QVector<ITarget> targets, Item item)
{
    this->actionType = actionType;
    this->user = user;
    this->targets = targets;
    this->item = item;
}


ITarget Action::getUser() const
{
    return this->user;
}

void Action::setUser(ITarget user)
{
    this->user = user;
}


Item Action::getItem() const
{
    return this->item;
}

void Action::setItem(Item item)
{
    this->item = item;
}

ActionType Action::getActionType() const
{
    return this->actionType;
}

void Action::setActionType(ActionType actionType)
{
    this->actionType = actionType;
}


QVector<ITarget> Action::getTargets() const
{
    return this->targets;
}

void Action::setTargets(QVector<ITarget> targets)
{
    this->targets = targets;
}
