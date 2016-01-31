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
    StatUsedItem(const StatUsedItem& s);

    virtual void apply(CurrentPlayer& player) const;
};

#endif // STATUSEDITEM_H
