#ifndef STATADDITEM_H
#define STATADDITEM_H

#include "istatupdate.h"
#include "types/item.h"

class StatAddItem : public IStatUpdate
{
    Item item;
public:
    StatAddItem(Item item);
    virtual void apply(CurrentPlayer& player);
};

#endif // STATADDITEM_H
