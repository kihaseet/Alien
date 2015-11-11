#ifndef STATCHARGEITEM_H
#define STATCHARGEITEM_H


#include "istatupdate.h"
#include "types/item.h"

class StatChargeItem : public IStatUpdate
{
    Item item;
public:
    StatChargeItem(Item item);
    StatChargeItem(const StatChargeItem& s);

    virtual void apply(CurrentPlayer& player) const;
};

#endif // STATCHARGEITEM_H
