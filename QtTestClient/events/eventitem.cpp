#include "eventitem.h"

EventItem::EventItem(QString what, QString who, QString target, ITarget item) : IEvent(what, who, target)
{
    this->item = item;
}

EventItem::EventItem(const EventItem &e) : IEvent(e.getWhat(), e.getWho(), e.getTarget())
{
    this->item = e.item;
}

QString EventItem::getDisplayMsg() const
{
    return who + " " + what + " " + item.getName() + (target.length() > 0 ? target : "");
}

