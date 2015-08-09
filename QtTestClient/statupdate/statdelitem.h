#ifndef STATDELITEM_H
#define STATDELITEM_H

#include "istatupdate.h"
#include "types/item.h"

class StatDelItem : public IStatUpdate
{
    Item item;
public:
    StatDelItem(Item item);
    virtual void apply(CurrentPlayer& player);
};

#endif // STATDELITEM_H
