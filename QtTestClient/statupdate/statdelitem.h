#ifndef STATDELITEM_H
#define STATDELITEM_H

#include "istatupdate.h"
#include "types/item.h"

class StatDelItem : public IStatUpdate
{
    Item item;
public:
    StatDelItem(Item item);
    StatDelItem(const StatDelItem& s);

    virtual void apply(CurrentPlayer& player) const;
};

#endif // STATDELITEM_H
