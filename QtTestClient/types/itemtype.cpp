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


QString ItemTypeProcess::ItemTypeToString(ItemType item)
{
    switch(item)
    {
    case IT_BADGE:
        return "Badge";
    case IT_BATTERY:
        return "Battery";
    case IT_BLASTER:
        return "Blaster";
    case IT_FETUS:
        return "Fetus";
    case IT_INJECTOR:
        return "Injector";
    case IT_MOP:
        return "Mop";
    case IT_NOTEBOOK:
        return "Notebook";
    case IT_ROTATION:
        return "Rotation";
    case IT_SCANNER:
        return "Scanner";
    case IT_UNKNOW:
        return "Unknown";
    }
}
