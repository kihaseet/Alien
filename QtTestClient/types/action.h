#ifndef ACTION_H
#define ACTION_H

#include <QVector>

#include "item.h"
#include "types/actiontype.h"

class Action
{
private:
    ITarget user;
    ITarget item;
    QVector<ITarget> targets;
    ActionType actionType;
public:
    explicit Action();
    explicit Action(ActionType actionType, ITarget user, QVector<ITarget> targets, ITarget item = Item(ItemType::IT_UNKNOW, 0));

    ITarget getUser();
    ITarget getItem();
    ActionType getActionType();
    QVector<ITarget> getTargets();
};

#endif // ACTION_H
