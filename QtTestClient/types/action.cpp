#include "types/action.h"

Action::Action()
{

}

Action::Action(ActionType actionType, ITarget user, QVector<ITarget> targets, ITarget item)
{
    this->actionType = actionType;
    this->user = user;
    this->targets = targets;
    this->item = item;
}


ITarget Action::getUser()
{
    return this->user;
}


ITarget Action::getItem()
{
    return this->item;
}

ActionType Action::getActionType()
{
    return this->actionType;
}


QVector<ITarget> Action::getTargets()
{
    return this->targets;
}

void Action::setTargets(QVector<ITarget> targets)
{
    this->targets = targets;
}
