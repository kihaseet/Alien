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

QMap<QString, TURN_TYPE> TurnObject::initColumnT()
{
    QMap<QString, TURN_TYPE> map;
    map.insert("useCap",TT_USE_BADGE);
    map.insert("use",TT_USE_ITEM);
    map.insert("ult",TT_ULT_ITEM);
    map.insert("wait",TT_SKIP);
    map.insert("up",TT_UP);
    map.insert("down",TT_DOWN);
    map.insert("attack",TT_ATTACK);
    map.insert("infect",TT_INFECT);
    map.insert("vote",TT_VOTE);
    map.insert("unvote",TT_UNVOTE);
    return map;
}

QMap<ROLE, ITEM> TurnObject::initColumnRT()
{
    QMap<ROLE, ITEM> map;
    map.insert(RT_CAPTAIN,IT_BADGE);
    map.insert(RT_ASSISTANT,IT_ROTATION);
    map.insert(RT_DOCTOR,IT_INJECTOR);
    map.insert(RT_ENGINEER,IT_BATTERY);
    map.insert(RT_GUNMEN,IT_BLASTER);
    map.insert(RT_SCIENTIST,IT_SCANNER);
    map.insert(RT_SIGNALMEN,IT_NOTEBOOK);
    return map;
}

QMap <QString, ITEM> TurnObject::ItemDescr = initColumnNames();
QMap <QString, TURN_TYPE> TurnObject::TurnDescr = initColumnT();
QMap <ROLE, ITEM> TurnObject::RoleItem = initColumnRT();
