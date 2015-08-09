#include "statdelitem.h"

StatDelItem::StatDelItem(Item item)
{
    this->item = item;
}

void StatDelItem::apply(CurrentPlayer &player)
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
