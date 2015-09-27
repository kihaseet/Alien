#ifndef STATADDITEM_H
#define STATADDITEM_H

#include "istatupdate.h"
#include "types/item.h"

class StatAddItem : public IStatUpdate
{
    Item item;
public:
    StatAddItem(Item item);
    StatAddItem(const StatAddItem& s);
    virtual void apply(CurrentPlayer& player) const;
};

#endif // STATADDITEM_H
