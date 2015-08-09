#ifndef ITEM_H
#define ITEM_H

#include "itarget.h"
#include "itemtype.h"

class Item : public ITarget
{
private:
    int charge;
    bool isActive;                  // Avaiable to use right now
    ItemType type;
public:
    Item();
    Item(ItemType type, int charge);

    int getChargeLevel();
    ItemType getType() const;
    void setChargeLevel(int charge);
    bool canUse();
    bool canUlt();
    void setActive(bool isActive);

    bool operator==(const Item& item) const;
};

#endif // ITEM_H
