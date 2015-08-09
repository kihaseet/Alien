#ifndef STATCHARGEITEM_H
#define STATCHARGEITEM_H


#include "istatupdate.h"
#include "types/item.h"

class StatChargeItem : public IStatUpdate
{
    Item item;
public:
    StatChargeItem(Item item);
    virtual void apply(CurrentPlayer& player);
};

#endif // STATCHARGEITEM_H
