#include "statupdatefactory.h"

StatUpdateFactory::StatUpdateFactory()
{

}

IStatUpdate StatUpdateFactory::addItem(Item item)
{
    return StatAddItem(item);
}

IStatUpdate StatUpdateFactory::usedItem(Item item, bool success)
{
    return StatUsedItem(item, success);
}

IStatUpdate StatUpdateFactory::delItem(Item item)
{
    return StatDelItem(item);
}

IStatUpdate StatUpdateFactory::alien()
{
    return StatAlien();
}

IStatUpdate StatUpdateFactory::changeHP(int HP)
{
    return StatChangeHP(HP);
}

