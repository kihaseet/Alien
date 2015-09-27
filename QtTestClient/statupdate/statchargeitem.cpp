#include "statchargeitem.h"

StatChargeItem::StatChargeItem(Item item)
{
    this->item = item;
}

StatChargeItem::StatChargeItem(const StatChargeItem &s)
{
    this->item = s.item;
}

void StatChargeItem::apply(CurrentPlayer &player) const
{
    auto items = player.getItems();
    for (Item& _item: items)
    {
        if (_item.getType() == this->item.getType())
        {
            if (_item.getType() != ItemType::IT_BADGE)
            {
                _item.setChargeLevel(-1);
            }
            else
            {
                _item.setChargeLevel(2);
            }
        }
    }

    player.setItems(items);
}
