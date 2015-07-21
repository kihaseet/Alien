#include "event.h"

QMap<QString, ITEM> TurnObject::initColumnNames()
{
    QMap<QString, ITEM> map;
    map.insert("Badge",IT_BADGE);
    map.insert("Injector",IT_INJECTOR);
    map.insert("Scanner",IT_SCANNER);
    map.insert("Mop",IT_MOP);
    map.insert("Battery",IT_BATTERY);
    map.insert("Blaster",IT_BLASTER);
    map.insert("Rotation",IT_ROTATION);
    map.insert("Notebook",IT_NOTEBOOK);
    return map;
}

QMap <QString, ITEM> TurnObject::ItemDescr = initColumnNames();
