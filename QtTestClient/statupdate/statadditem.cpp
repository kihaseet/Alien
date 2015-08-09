#include "statadditem.h"

StatAddItem::StatAddItem(Item item)
{
    this->item = item;
}

void StatAddItem::apply(CurrentPlayer &player)
{
    auto items = player.getItems();
    items.push_back(this->item);
    player.setItems(items);
}
