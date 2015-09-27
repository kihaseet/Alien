#include "statdelitem.h"

StatDelItem::StatDelItem(Item item)
{
    this->item = item;
}

StatDelItem::StatDelItem(const StatDelItem &s)
{
    this->item = s.item;
}

void StatDelItem::apply(CurrentPlayer &player) const
{
    auto items = player.getItems();
    for (Item& item: items)
    {
        if (item.getName() == this->item.getName())
        {
            items.removeAll(item);
            break;
        }
    }

    player.setItems(items);
}
