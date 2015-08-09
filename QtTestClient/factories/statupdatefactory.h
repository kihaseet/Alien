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
    static IStatUpdate addItem(Item item);
    static IStatUpdate usedItem(Item item, bool success);
    static IStatUpdate delItem(Item item);
    static IStatUpdate alien();
    static IStatUpdate changeHP(int HP);
};

#endif // STATUPDATEFACTORY_H
