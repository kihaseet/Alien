#include "eventitem.h"

EventItem::EventItem(QString what, QString who, QString target, ITarget item) : IEvent(what, who, target)
{
    this->item = item;
}

QString EventItem::getDisplayMsg()
{
    return who + " " + what + " " + item.getName() + (target.length() > 0 ? target : "");
}

