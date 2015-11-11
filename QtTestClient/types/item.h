#ifndef ITEM_H
#define ITEM_H

#include <QVector>

#include "itarget.h"
#include "itemtype.h"

class Item : public ITarget
{
private:
    int charge;
    bool isActive;                  // Avaiable to use right now
    bool batteryBlessing;
    ItemType type;
public:
    Item();
    Item(ItemType type, int charge);

    int getChargeLevel();
    ItemType getType() const;
    void setChargeLevel(int charge);
    void setBatteryBlessing(bool blessing);
    bool getBatteryBlessing();
    bool canUse();
    bool canUlt();
    void setActive(bool isActive);

    bool operator==(const Item& item) const;
};

#endif // ITEM_H
