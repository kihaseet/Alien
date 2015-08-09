#include "statuseditem.h"

StatUsedItem::StatUsedItem(Item item, bool success)
{
    this->item = item;
    this->success = success;
}

void StatUsedItem::apply(CurrentPlayer &player)
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
                    _item.setChargeLevel(2);
                }
            }
        }

        player.setItems(items);
    }
}
