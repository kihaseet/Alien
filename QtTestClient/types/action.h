#ifndef ACTION_H
#define ACTION_H

#include <QVector>

#include "item.h"
#include "types/actiontype.h"

class Action
{
private:
    ITarget user;
    Item item;
    QVector<ITarget> targets;
    ActionType actionType;
public:
    explicit Action();
    explicit Action(ActionType actionType, ITarget user, QVector<ITarget> targets, Item item = Item(ItemType::IT_UNKNOW, 0));

    ITarget getUser() const;
    void setUser(ITarget user);

    Item getItem() const;
    void setItem(Item item);

    ActionType getActionType() const;
    void setActionType(ActionType actionType);

    QVector<ITarget> getTargets() const;
    void setTargets(QVector<ITarget> targets);
};

#endif // ACTION_H
