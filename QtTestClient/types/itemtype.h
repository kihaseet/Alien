#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <QString>

enum ItemType
{
    IT_UNKNOW = -1,
    IT_BADGE = 0,
    IT_INJECTOR,
    IT_SCANNER,
    IT_MOP,
    IT_BATTERY,
    IT_BLASTER,
    IT_NOTEBOOK,
    IT_ROTATION,
    IT_FETUS
};

#define ITEMTYPE_LAST 8

namespace ItemTypeProcess
{
    ItemType ItemTypeByName(QString it);
    QString ItemTypeToString(ItemType item);
}

#endif // ITEMTYPE_H
