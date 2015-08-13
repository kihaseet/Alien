#ifndef EVENTITEM_H
#define EVENTITEM_H

#include "types/itarget.h"
#include "ievent.h"

#include <QString>


class EventItem : public IEvent
{
    ITarget item;
public:
    EventItem(QString what, QString who, QString target, ITarget item);
    EventItem(const EventItem& e);
    virtual QString getDisplayMsg() const;
};

#endif // EVENTITEM_H
