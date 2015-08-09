#ifndef STATUSEDITEM_H
#define STATUSEDITEM_H

#include "istatupdate.h"
#include "types/item.h"

class StatUsedItem : public IStatUpdate
{
    Item item;
    bool success;
public:
    StatUsedItem(Item item, bool success);
    virtual void apply(CurrentPlayer& player);
};

#endif // STATUSEDITEM_H
