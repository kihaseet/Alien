#include "statuseditem.h"

StatUsedItem::StatUsedItem(Item item, bool success)
{
    this->item = item;
    this->success = success;
}

StatUsedItem::StatUsedItem(const StatUsedItem &s)
{
    this->item = s.item;
    this->success = s.success;
}

void StatUsedItem::apply(CurrentPlayer &player) const
{
    if (success)
    {
        auto items = player.getItems();
        for (Item& _item: items)
        {
            if (_item.getType() == this->item.getType())
            {
                if (_item.getType() == ItemType::IT_BADGE)
                {
                    _item.setChargeLevel(-1);
                }
                else
                {
                    if (_item.getBatteryBlessing())
                    {
                        _item.setBatteryBlessing(false);
                    }
                    else
                    {
                        _item.setChargeLevel(2);
                    }
                }
            }
        }

        player.setItems(items);
    }
}
