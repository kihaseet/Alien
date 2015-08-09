#include "itemtype.h"

ItemType ItemTypeProcess::ItemTypeByName(QString it)
{
    if (it == "Unknown")
    {
        return IT_UNKNOW;
    }
    else if (it == "Badge")
    {
        return IT_BADGE;
    }
    else if (it == "Injector")
    {
        return IT_INJECTOR;
    }
    else if (it == "Scanner")
    {
        return IT_SCANNER;
    }
    else if (it == "Mop")
    {
        return IT_MOP;
    }
    else if (it == "Battery")
    {
        return IT_BATTERY;
    }
    else if (it == "Blaster")
    {
        return IT_BLASTER;
    }
    else if (it == "Notebook")
    {
        return IT_NOTEBOOK;
    }
    else if (it == "Rotation")
    {
        return IT_ROTATION;
    }
}
