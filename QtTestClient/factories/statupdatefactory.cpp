#include "statupdatefactory.h"

StatUpdateFactory::StatUpdateFactory()
{

}

StatAddItem StatUpdateFactory::addItem(Item item)
{
    return StatAddItem(item);
}

StatUsedItem StatUpdateFactory::usedItem(Item item, bool success)
{
    return StatUsedItem(item, success);
}

StatDelItem StatUpdateFactory::delItem(Item item)
{
    return StatDelItem(item);
}

StatAlien StatUpdateFactory::alien()
{
    return StatAlien();
}

StatChangeHP StatUpdateFactory::changeHP(int HP)
{
    return StatChangeHP(HP);
}

