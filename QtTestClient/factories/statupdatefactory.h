#ifndef STATUPDATEFACTORY_H
#define STATUPDATEFACTORY_H

#include "types/item.h"
#include "statupdate/istatupdate.h"
#include "statupdate/statadditem.h"
#include "statupdate/statalien.h"
#include "statupdate/statchangehp.h"
#include "statupdate/statdelitem.h"
#include "statupdate/statuseditem.h"

class StatUpdateFactory
{
public:
    StatUpdateFactory();
    static StatAddItem addItem(Item item);
    static StatUsedItem usedItem(Item item, bool success);
    static StatDelItem delItem(Item item);
    static StatAlien alien();
    static StatChangeHP changeHP(int HP);
};

#endif // STATUPDATEFACTORY_H
