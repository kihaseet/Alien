#include "statadditem.h"

StatAddItem::StatAddItem(Item item)
{
    this->item = item;
}

StatAddItem::StatAddItem(const StatAddItem &s)
{
    this->item = item;
}

void StatAddItem::apply(CurrentPlayer &player) const
{
    auto items = player.getItems();
    items.push_back(this->item);
    player.setItems(items);
}
